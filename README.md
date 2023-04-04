# Windows-Keylogger
Certainly, here's an example disclaimer that can be displayed prominently in your repository:

DISCLAIMER:

This code is for educational and research purposes only. The author does not condone or support the use of this code for any illegal or unethical activities. The author is not responsible for any harm caused by the use or misuse of this code.

By accessing and/or using this code, you agree to use it solely for educational and research purposes and to comply with all applicable laws and regulations. You assume full responsibility for any actions taken based on the information and code provided in this repository.

This code is provided as-is, without warranty of any kind, express or implied. The author disclaims any and all liability for any damages or losses arising from the use or inability to use this code.

The use of this code for any illegal or unethical activities is strictly prohibited. If you choose to use this code, you do so at your own risk and acknowledge that you may be subject to legal consequences.









This code is a Windows program that captures the state of certain keys on the keyboard and sends them to a server. The program includes the necessary libraries for socket programming and keyboard input handling.

The send_data function is responsible for establishing a connection to the server and sending the data provided as an argument. It first initializes the Winsock library using WSAStartup. It then creates a socket using socket with the AF_INET address family, SOCK_STREAM socket type, and IPPROTO_TCP protocol. It resolves the server address using InetPton and the SERVER_ADDRESS and SERVER_PORT macros defined at the top of the program. It connects to the server using connect, passing the sockfd, a pointer to the serverAddr structure, and its size. If the connection fails, it cleans up and returns -1. Otherwise, it sends the data using send, passing the sockfd, the data, its length, and 0 as the flags. It then closes the socket and cleans up the Winsock library. Finally, it returns the number of bytes sent.

The get_keyboard_state function captures the state of the VK_SPACE, VK_CONTROL, VK_SHIFT, and VK_MENU keys and sends the captured keystrokes to the server using the send_data function. It uses GetKeyboardState to retrieve the current state of the keyboard and stores it in the keyboard_state array. It then checks if each of the keys is pressed by testing if the corresponding bit is set in the keyboard_state array using bitwise AND with 0x80. If a key is pressed, it sets the corresponding bit in the result variable using bitwise OR. Finally, it formats the keystrokes into a string and sends it to the server using send_data. It returns the result variable, which represents the state of the keys as a bitfield with 4 bits.
