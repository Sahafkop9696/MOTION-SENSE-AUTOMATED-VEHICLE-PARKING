import serial
import time

# Set up the serial connection to Arduino
arduino = serial.Serial('COM3', 9600, timeout=1)  # Change COM port as needed
time.sleep(2)  # Wait for Arduino to reset

def check_parking_status():
    while True:
        # Read the data from Arduino
        if arduino.in_waiting > 0:
            data = arduino.readline().decode('utf-8').strip()
            print(data)
            # Check if the parking is full
            if "Parking Full!" in data:
                print("Parking lot is full. Please wait for a spot to open.")
        
        time.sleep(1)  # Delay between each read to avoid overwhelming the serial buffer

if __name__ == "__main__":
    check_parking_status()
