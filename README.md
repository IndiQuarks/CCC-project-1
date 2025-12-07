_Linked List Music Player on ESP32_
*Demonstrating a Circular Singly Linked List Using Sound Playback*

This project demonstrates how a circular singly linked list can be implemented on an ESP32 and used to control the playback of multiple songs using a passive buzzer. Each node in the linked list represents one complete song, and the ESP32 continuously traverses the list, playing each song in sequence.

This serves as a practical example of applying data structures and algorithms (DSA) concepts to embedded systems programming.

`Features`

Four songs stored as independent linked list nodes

Circular linked list implementation

Automatic traversal using pointer-based linking

Non-blocking note scheduling using millis()

Compatible with passive buzzers through a transistor driver circuit

Clear mapping between DSA concepts and hardware behavior

Data Structure Used

The system is built around a singly linked circular list. Each node contains:

A pointer to a frequency array

A pointer to a duration array

The number of notes

A pointer to the next node

Node definition:

struct Song {
  const uint16_t* freqs;
  const uint16_t* durs;
  uint8_t length;
  Song* next;
};


Nodes are linked manually in setup():

songDhoom.next = &songHB;
songHB.next = &songNokia;
songNokia.next = &songSnake;
songSnake.next = &songDhoom;


This creates a circular playlist:

Dhoom -> Happy Birthday -> Nokia -> Snake -> Dhoom -> ...


Traversal occurs through:

currentSong = currentSong->next;


This line expresses the core linked list behavior.

Hardware Requirements

ESP32 Dev Module

Passive buzzer

2N2222 NPN transistor

1k resistor (base)

10k resistor (base pulldown)

220Ω resistor (series with buzzer)

Breadboard and jumper wires

Wiring Guide

Recommended circuit for safe and amplified buzzer output:

ESP32 3.3V ---- 220Ω ----> Buzzer (+)
Buzzer (–) ----> Collector (2N2222)
Emitter (2N2222) ----> GND

ESP32 GPIO 18 ---- 1k ----> Base (2N2222)
Base (2N2222) ---- 10k ----> GND


This prevents overloading the ESP32 pin and improves audio stability.

Code Overview
Node Creation

Each song is represented as a struct containing arrays of frequencies and durations:

Song songDhoom = { dhoom_freqs, dhoom_durs, length, nullptr };

Linked List Setup

The songs are chained into a circular list inside setup().

Playback Logic

In loop():

The current note frequency is retrieved from the current node.

playNote() uses LEDC hardware PWM to output the tone.

When a note completes, the index advances.

When a song completes, the pointer moves to the next node in the list.

This produces continuous playback controlled by linked list traversal.

Educational Value

The project demonstrates:

How linked lists work on a low level using pointers

Circular list behavior in a practical setting

Event scheduling without blocking using millis()

Mapping abstract DSA concepts to embedded hardware output

This makes it useful for coursework, lab demonstration, or introductory DSA concepts taught through physical computing.

Running the Project

Connect the hardware as described.

Upload the provided code to the ESP32 using Arduino IDE.

Power the ESP32.

The device begins traversing the linked list and playing each song in sequence.

Possible Extensions

Add a push-button or TFT touch input to skip songs

Display the linked list visually on an attached TFT

Convert to a doubly linked list and allow forward/backward navigation

Add dynamic node insertion or deletion at runtime

Implement a full audio playlist UI

If you want to expand the project in any of these directions, additional code can be provided.
