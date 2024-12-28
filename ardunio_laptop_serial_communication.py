import serial
import time

# Initialize the serial connection
# Replace 'COM3' with Arduino's COM port 
arduino = serial.Serial('COM3', 9600)  
time.sleep(2)  # Allow time for Arduino to reset

def send_char_to_arduino(char):
    """
    Send a single character to the Arduino via serial communication.
    """
    arduino.write(char.encode())  # Convert character to bytes and send
    print(f"Sent: {char}")

def main():
    try:
        print("Braille Reader Communication Started!")
        print("Type your message below. Type 'exit' to quit.\n")
        
        while True:
            # Get user input
            message = input("Enter a message: ")
            
            if message.lower() == 'exit':  # Exit the program
                print("Exiting the Braille Reader.")
                break
            
            # Send each character in the message to Arduino
            for char in message:
                send_char_to_arduino(char)
                time.sleep(1)  # Delay between sending characters (adjust as needed)
    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        arduino.close()  # Ensure the serial connection is closed
        print("Serial connection closed.")

# Run the script
if __name__ == "__main__":
    main()
