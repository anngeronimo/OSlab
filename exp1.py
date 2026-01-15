import os
import sys

pid = os.fork()
if pid < 0:
    print("fork failed")
    sys.exit(1)
elif pid == 0:
    os.execlp("whoami", "whoami")
else:
    print(f"\nProcess ID is: {os.getpid()}\n")
    os.wait()
    sys.exit(0)