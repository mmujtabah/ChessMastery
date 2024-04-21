# ChessMastery

## Overview
ChessMastery is a project developed as part of the second semester project for Object-Oriented Programming (OOP) at FAST-NUCES. Collaboratively completed with my project partner [Harris](https://github.com/MHarrisT). This project features various OOP aspects such as classes, pointers, inheritance, abstraction, and polymorphism.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Gameplay](#gameplay)
- [Contributing](#contributing)
- [License](#license)

## Features

- **Interactive Chess Board**: Provides users with an interactive chess board for playing against each other.

- **Interactive Sounds**: Engaging sounds are played when a piece is moved, captured, promoted, or to announce the winner.
 
- **Mouse Handling**: Players can use their mouse to right-click a piece to view its valid moves and then left-click the desired chessboard cell to execute the move.

## Getting Started

### Prerequisites

- C++ compiler
- SFML library (version 2.6.1)

### Installation

To install ChessMastery, follow these steps:

1. Clone the repository to your local machine: ```git clone https://github.com/mmujtabah/ChessMastery.git```

2. Navigate to the project directory:

   ```cd ChessMastery```

3. Compile the source code:

   ```g++ ChessMastery.cpp ChessWindow.cpp ChessPiece.cpp -o ChessMastery -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio```

4. Configure the project settings as needed.

### Usage

Run the compiled executable: `./ChessMastery`

## Gameplay

ChessMastery offers a comprehensive gaming experience with the following features:

- White pieces start the game, with players taking alternating turns.
- Each turn, players can move only one piece of their color.
- The game objective is to capture the opposing color's king to win.
- Captured pieces are displayed on the left side of the window, organized by color.

## Contributing

Contributions to ChessMastery are welcome! Here's how you can contribute:

- Fork the repository.
- Create a new branch for your feature or bug fix.
- Make your changes and commit them with descriptive messages.
- Push your changes to your fork.
- Submit a pull request to the main repository.

Please ensure that your contributions adhere to the project's coding standards and guidelines.

## Acknowledgments

- [SFML Library](https://www.sfml-dev.org/) - Simple and Fast Multimedia Library.

## License

This project is licensed under the [MIT License](LICENSE).