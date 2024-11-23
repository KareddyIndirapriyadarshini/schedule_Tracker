# Schedule Tracker

A task management application built using C++ that organizes tasks by date using **linked lists**. The Schedule Tracker allows users to manage their tasks effectively by adding tasks with specific priorities and recurrence, viewing all tasks sorted by priority, and displaying upcoming tasks.

---

## Features

- **Add Task**: Add tasks with a description, priority (high, medium, low), and recurrence (none, daily, weekly, monthly) for a specific date.
- **Display All Tasks**: View all tasks sorted by priority using linked list traversal.
- **Display Future Tasks**: View tasks scheduled for dates after the current day.
- **Recurring Tasks**: Automatically handle tasks with daily, weekly, or monthly recurrence.
- **Input Validation**: Ensures only valid dates and correct inputs are accepted.

---

## How It Works

This project is implemented using **linked lists** to manage tasks and dates efficiently:

1. **Date Linked List**: Each date is represented as a node (`DateNode`) in a linked list.
   - Contains the day, month, year, and a pointer to the task list for that date.

2. **Task Linked List**: Each date node maintains a linked list of tasks (`Task`).
   - Contains the task description, priority, recurrence type, and a pointer to the next task.

3. Operations like adding, displaying, and managing tasks are performed through traversal and manipulation of these linked lists.

---
