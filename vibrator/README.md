# Qin SC27xx vibrator HAL

The 4.14 sc27xx-vibra driver exposes an input device named
sc27xx:vibrator with FF_RUMBLE. It has no timed_output/LED enable node,
so the stock default vibrator HAL cannot drive it.

This HIDL 1.0 service finds the named evdev node and uses EVIOCSFF,
EV_FF playback/stop, and EVIOCRMFF. An interruptible monotonic worker
stops requests at the deadline; off() cancels a pending timer.
Unsupported predefined effects use the framework's fallback.
The motor does not support amplitude control.

The rc runs as system with the input group. The VINTF fragment and full
/system/vendor executable label are packaged with the module.
Extended ioctls are limited to EVIOCGNAME, EVIOCSFF and EVIOCRMFF.

qin_vibrator_probe is not in PRODUCT_PACKAGES. The user confirmed its
500 ms motor pulse on the actual device. Framework validation uses
cmd vibrator_manager list, synced -f oneshot 500 and dumpsys.
