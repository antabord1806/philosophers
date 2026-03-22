# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/).

## [Unreleased]

## [1.0.0] - 2026-03-22

### Added
- Initial project implementation: Dining Philosophers concurrency simulation using POSIX threads and mutexes.
- `philo/` directory with full source code:
  - `p_meal_check.c` — monitor thread that checks if philosophers have eaten enough.
  - `p_monitor.c` — monitor logic for detecting philosopher deaths.
  - `p_routine.c` — main loop executed by each philosopher thread.
  - `p_single_philo.c` — special-case handling for a single philosopher.
  - `p_threads.c` — thread creation and lifecycle management.
  - `include/philo.h` and `include/structs.h` — shared headers and data structures.
  - `Makefile` with standard rules (`all`, `clean`, `fclean`, `re`).
- `README.md` with project overview, usage instructions, key concepts (race condition, deadlock, starvation, mutexes), and test examples.

### Changed
- README: corrected grammatical errors in English text and translated remaining Portuguese sections to English.
