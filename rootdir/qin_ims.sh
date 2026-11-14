#!/vendor/bin/sh
# Qin 2 Pro: keep modem-side IMS (VoLTE) enabled.
#
# The SC9863A runs the IMS stack inside the modem. On stock, the Unisoc
# ims.apk asks sprdrild (IExtRadio) to send AT+IMSEN=1; LineageOS has no such
# client, so IMS never registers (+CIREG: x,0) and calls fail with cause 34
# (China Mobile has no usable 2G/CSFB here). Once IMSEN=1 is sent, the modem
# registers IMS within ~1 s and plain ATD calls go out over VoLTE.
#
# Uses a spare AT channel (stty_lte20) not opened by sprdrild/modemd/engpc.
# Sends IMSEN=1 only when LTE is registered and IMS is not.

TTY=/dev/stty_lte20
TAG=qin_ims

at() {
    exec 3<>"$TTY" || return 1
    printf '%s\r' "$1" >&3
    timeout 3 cat <&3 | tr -d '\r'
    exec 3>&-
}

field2() {
    # "+CIREG:2,1,0" / "+CEREG: 2,1,..." -> second number
    grep -o "$1: *[0-9]*,[0-9]*" | head -1 | cut -d, -f2
}

last=""
while true; do
    if [ "$(getprop persist.vendor.sys.volte.enable)" != "false" ] && [ -c "$TTY" ]; then
        ims=$(at 'AT+CIREG?' | field2 '+CIREG')
        if [ "$ims" != "1" ]; then
            lte=$(at 'AT+CEREG?' | field2 '+CEREG')
            if [ "$lte" = "1" ] || [ "$lte" = "5" ]; then
                r=$(at 'AT+IMSEN=1' | tr '\n' ' ')
                log -t "$TAG" "IMS not registered (CIREG=$ims, CEREG=$lte): AT+IMSEN=1 -> $r"
            fi
        elif [ "$last" != "1" ]; then
            log -t "$TAG" "IMS registered"
        fi
        last=$ims
    fi
    sleep 20
done
