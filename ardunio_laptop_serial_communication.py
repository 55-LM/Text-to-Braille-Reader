import serial
import time
import sys

arduino = serial.Serial('COM3', 9600, timeout=1)
time.sleep(2)

def send_message(message):
    if not message.endswith("\n"):
        message += "\n"
    arduino.write(message.encode("utf-8", errors="ignore"))
    arduino.flush()

def main():
    try:
        print("Paste or type text. It will display 5 Braille cells at a time.")
        print("Press the hardware button to advance to the next 5 characters.")
        print("Type exit to quit.\n")

        while True:
            try:
                message = input("Enter text: ")
            except EOFError:
                break

            if message.strip().lower() == "exit":
                break

            send_message(message)
            time.sleep(0.05)

    except KeyboardInterrupt:
        pass
    finally:
        try:
            arduino.close()
        except Exception:
            pass

if __name__ == "__main__":
    main()
