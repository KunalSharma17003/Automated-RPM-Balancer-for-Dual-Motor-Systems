# Automated RPM Balancer for Dual-Motor Systems Using FreeRTOS

This repository contains the **Automated RPM Balancer for Dual-Motor Systems**, a project designed to tackle synchronization challenges in dual-motor setups, particularly for autonomous vehicles. The system leverages **FreeRTOS**, a real-time operating system, to deliver precise and adaptive control, ensuring both wheels rotate in harmony. This precision is crucial for maintaining vehicle stability during navigation, especially on uneven terrain or when executing sharp turns.

### Features and Implementations

1. **Optical Encoder Integration**  
   - Optical encoders provide real-time feedback on wheel rotation by detecting pulse trains from a patterned optical disc.  
   - These pulses are converted into RPM, enabling precise speed measurements for both motors.

2. **Real-Time Task Management with FreeRTOS**  
   - **Task Priority Management**: Ensures critical tasks, such as obstacle detection, are executed promptly.  
   - **Task Yielding**: Enhances responsiveness by allowing idle tasks to release the processor.  
   - **Dynamic Task Suspension and Resumption**: Ensures safety by suspending motor-related tasks during obstacle detection.

3. **Pulse Width Modulation (PWM) for Speed Control**  
   - Motor speeds are dynamically synchronized by adjusting the duty cycle of PWM signals.  
   - Compensates for natural discrepancies caused by manufacturing or environmental conditions.

4. **Queue-Based Data Handling**  
   - FreeRTOS queues ensure efficient and corruption-free data transfer between tasks.  
   - Enhances memory integrity and system reliability.

5. **Efficient Memory Management**  
   - **Stack Monitoring**: Utilizes `uxTaskGetStackHighWaterMark()` to optimize stack allocation.  
   - System uses only 34% of flash memory and 23% of SRAM, leaving room for future enhancements.

6. **Adaptive Synchronization Algorithm**  
   - Compares RPM feedback from encoders in real time.  
   - Dynamically adjusts PWM signals to equalize motor speeds, ensuring precise synchronization and stable wheel motion.

### Project Significance

This project showcases the potential of **FreeRTOS** in developing advanced embedded systems with real-time control, optimized resource usage, and robust responsiveness. The **Adaptive RPM Balancer** provides a foundation for innovations in autonomous vehicle technology, addressing critical synchronization challenges in dual-motor systems.

### Potential Applications
- Autonomous ground vehicles (AGVs)  
- Robotics with dual-motor setups  
- Precision control systems for industrial automation  

Explore the repository to learn more about the implementation, code structure, and future enhancement possibilities!
