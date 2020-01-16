import serial
import time

ser = serial.Serial('COM11', baudrate=250000, timeout=1)
time.sleep(3)

numpoints = 10
size_of_data = 7030
data_list = [0]*size_of_data
data_index = 0


def get(index):
    if index >= size_of_data-1:
        index = 0
        return index
    else:
        fg = ''
        ser.write(b'g')
        while fg != b'm':
            fg = ser.read()
        for i in range(numpoints):
            str_input = ser.readline().decode().split('\r\n')
            data = int(str_input[0])
            data_list[index] = data
            index += 1
        print(f"{data_index} B")
        return index


def erase():
    ser.write(b'e')


def convert_file():
    user_choice = input("press f for convert to file")
    if user_choice == 'f':
        out_file = "test_5.2.bmp"  # put output file name with extension
        test_out = open(out_file, "wb")
        byte_array = bytearray(data_list)
        test_out.write(byte_array)


while 1:
    rx_command = ser.read()
    if rx_command == b'r':
        data_index = get(data_index)
        erase()
        if data_index == 0:
            break


convert_file()


