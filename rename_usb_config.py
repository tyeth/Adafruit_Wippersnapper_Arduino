# import os

# Import("env")

# print("** RENAME_USB_CONFIG.PY run")

# adafruit_usb_config = os.path.join(
#     env.subst("$PROJECT_LIBDEPS_DIR"),
#     env.subst("$PIOENV"),
#     "Adafruit TinyUSB Library",
#     "src",
#     "tusb_config.h",
# )

# print("Test before rename passes: (",adafruit_usb_config,")")
# print(os.path.isfile(adafruit_usb_config))

# if os.path.isfile(adafruit_usb_config):
#     os.rename(adafruit_usb_config, adafruit_usb_config + "_backup")

# print("** EOF **")