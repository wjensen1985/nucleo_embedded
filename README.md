# nucleo_embedded
## some commands to remember:
- usbipd in windows powershell w/admin
    - usbipd --list
    - attach to wsl: usbipd attach --wsl busid ID-ID
        - detach: usbipd detach -b ID-ID
- verify can see in wsl with lsusb
- screen session for sending over usb:
    - check name to use, run command: ls /dev/tty* -> find stm device, usually ACM0
    - start session: screen /dev/ttyACM0 115200 8N1
        - screen -r to rejoin session (ctrl+z to exit within session)
    - to kill session once exited:
        - screen -ls to get session id: sessionID.pts-....
        - screen -S sessionID -X quit
- flashing board from vscode:
    - Run and debug -> run the launch task (ST-Link: debug application)
    - It will hit breakpoint before running, hit run/continue -> board program should start running now
        - can close/stop debug task session