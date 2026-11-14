#include <unistd.h>
#include <sys/system_properties.h>
/* The stock bootanim GL thread crashes if it starts before the display
 * pipeline is ready; delaying it ~20s avoids the crash window. Init cannot
 * exec shell scripts under SELinux enforcing (execute_no_trans is
 * neverallowed), so this tiny helper asks init to start the real service.
 */
int main(void) {
    sleep(20);
    __system_property_set("ctl.start", "bootanim");
    return 0;
}
