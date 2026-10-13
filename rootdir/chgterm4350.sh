#!/system/bin/sh
# chgterm4350: keep fan54015 charge termination at the battery's rated voltage.
#
# The stock kernel leaves the fan54015 at power-on defaults:
#   REG_2 VOREG = 4.2V, REG_6 VSAFE = 0 (hardware clamps VOREG <= ~4.2V).
# This cell is a 4.35V battery (see dtb battery node), so charging stalls
# at ~4.2V (~91% SOC) forever. There is no writable sysfs and the kernel
# driver never re-programs these registers, so we do it here and re-apply
# after any boot/replug event that may reset them.

BUS=4
ADDR=0x6a
REG_VOREG=0x2
REG_SAFE=0x6
DTB=/proc/device-tree/battery/constant_charge_voltage_max_microvolt
POLL=20

# Battery terminal voltage in mV: big-endian u32 uV from the dtb battery
# node, fallback 4350000.
read_vol_mv() {
    hex=$(od -A n -t x1 -v -N 4 "$DTB" 2>/dev/null | tr -d ' \n')
    [ -n "$hex" ] && echo $((0x$hex / 1000)) || echo 4350
}

VOL_MV=$(read_vol_mv)
[ "$VOL_MV" -lt 3500 ] && VOL_MV=3500
[ "$VOL_MV" -gt 4440 ] && VOL_MV=4440

# VOREG bits[7:2] = (mV-3500)/20 ; VSAFE bits[3:0] = (mV-4200)/20+1
VOREG=$(( (VOL_MV - 3500) / 20 ))
[ "$VOREG" -gt 46 ] && VOREG=46
if [ "$VOL_MV" -le 4200 ]; then VSAFE=1; else
    VSAFE=$(( (VOL_MV - 4200) / 20 + 1 )); [ "$VSAFE" -gt 15 ] && VSAFE=15
fi

log -t chgterm4350 "start: vol=${VOL_MV}mV voreg=0x$(printf %x $VOREG) vsafe=0x$(printf %x $VSAFE)"

while :; do
    r2=$(i2cget -y -f $BUS $ADDR $REG_VOREG 2>/dev/null) || r2=""
    r6=$(i2cget -y -f $BUS $ADDR $REG_SAFE 2>/dev/null) || r6=""
    [ -n "$r2" ] && r2=$((r2)) || r2=-1
    [ -n "$r6" ] && r6=$((r6)) || r6=-1
    if [ "$r2" -ge 0 ] && [ "$r6" -ge 0 ]; then
        if [ $((r6 & 15)) -ne "$VSAFE" ]; then
            i2cset -y -f $BUS $ADDR $REG_SAFE $(((r6 & 240) | VSAFE)) b
            log -t chgterm4350 "vsafe: reg6 0x$(printf %02x $r6) -> 0x$(printf %02x $(((r6 & 240) | VSAFE)))"
        fi
        if [ $(((r2 >> 2) & 63)) -ne "$VOREG" ]; then
            i2cset -y -f $BUS $ADDR $REG_VOREG $(((VOREG << 2) | (r2 & 3))) b
            log -t chgterm4350 "voreg: reg2 0x$(printf %02x $r2) -> 0x$(printf %02x $(((VOREG << 2) | (r2 & 3))))"
        fi
    fi
    sleep $POLL
done
