K.O.R.E.

Kat Orchestration Runtime Engine

K.O.R.E. is an open-source ecosystem that combines embedded firmware and cross-platform desktop/mobile applications into a single intelligent companion experience.

Overview

K.O.R.E. consists of two main projects:

* KORE_OS — Firmware running on an ESP32-S3 device.
* COMPANION — Cross-platform applications for macOS, Windows, Linux, iOS and Android.

The goal is to provide a seamless interaction between hardware and software through a modular, maintainable and scalable architecture.

⸻

## Project Structure

```text

.

├── COMPANION/
│   ├── android/
│   ├── ios/
│   ├── linux/
│   ├── macos/
│   ├── shared/
│   └── windows/
│
├── KORE_OS/
│
├── SPEC/
├── ADR/
└── HARNESS/

```

⸻

## Technology Stack

Firmware

* ESP32-S3
* Arduino Framework

Companion Applications

* React
* Tauri
* Swift (platform-specific integrations)

⸻

## Development Philosophy

K.O.R.E. follows a Specification Driven Development (SDD) workflow.

Every feature begins with a specification before implementation.

Development is performed incrementally, module by module, ensuring that each module is validated before the next one begins.

Core principles:

* Clean architecture
* Modular design
* Incremental development
* High maintainability
* Documentation-first
* Test-driven validation

⸻

## AI-Assisted Development

K.O.R.E. adopts specialized AI agents with clearly defined responsibilities.

Gaspar

Software architect.

Responsible for:

* Architecture
* Specifications
* Technical reviews
* Architectural consistency

Belthazar

Primary implementation agent.

Powered by:

* OpenCode
* DeepSeek V4 Flash Free

Responsible for:

* Implementation
* Refactoring
* Testing

Melchior

UI/UX specialist.

Powered by:

* Gemini CLI
* UI/UX Pro Max

Responsible for:

* User Interface
* User Experience
* React component design
* Design System

⸻

## Documentation

Project documentation is organized as follows:

* PROJECT.md — Project overview and philosophy
* SPEC/ — Functional specifications
* ADR/ — Architecture Decision Records
* HARNESS/ — Implementation tasks
* AGENTS.md — Belthazar implementation guidelines
* GEMINI.md — Melchior UI/UX guidelines

Documentation is the single source of truth.

⸻

## Status

🚧 K.O.R.E. is currently under active development. Currently in v1.0.0 for KORE_OS and COMPANION APP (mac os)

The repository is being rebuilt from the ground up using a Specification Driven Development workflow.

⸻

License

This project is licensed under the MIT License.
