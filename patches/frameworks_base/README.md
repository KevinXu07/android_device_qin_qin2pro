# Qin SystemUI diagnostic override

Apply systemui_strictmode_override.patch from frameworks/base before building.
Honor explicit persist.sysui.strictmode=false on eng builds; keep the
eng default when unset. Qin disables the flashing red diagnostic border.
