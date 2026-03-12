# Text Label Manager

## Overview
This project is an implementation of a Label management system, developed as an assignment to demonstrate proficiency in **Structural Design Patterns**.

The application provides a flexible architecture for creating, transforming, and decorating text labels. It enables dynamic styling, text manipulation, and complex behavior composition using patterns like Decorator, Strategy, Composite, Proxy, Bridge, and Flyweight.

## Features

### 1. Label Types
* **SimpleLabel:** Basic container for text strings.
* **RichLabel:** Extends basic functionality to include styling attributes such as **Color**, **Font Name**, and **Font Size**.
* **Proxy Label (Custom Label):** A label that lazily reads its text from Standard Input (CLI) upon the first request. It includes a **timeout mechanism** that allows users to refresh or keep the current text after a specific period.

### 2. Text Transformations
A robust transformation engine that can be applied to any label:
* **Capitalize:** Capitalizes the first letter if it is an alphabet character.
* **Trim (Left/Right):** Removes whitespace from the beginning or end of the text.
* **Normalize Space:** Collapses multiple consecutive spaces into a single space.
* **Decorate:** Wraps the text in a custom bracket style (e.g., `-={ text }=-`).
* **Censor:** Replaces specific words with asterisks (`***`).
* **Replace:** Performs case-sensitive string replacement.

### 3. Advanced Label Manipulation
* **Dynamic Decorators:** Apply transformations (Capitalize, Trim, etc.) dynamically at runtime.
    * *Random Decorator:* Applies a random transformation from a provided list.
    * *Cycling Decorator:* Cycles through a list of transformations sequentially on each call.
* **Composite Transformations:** Group a sequence of transformations to act as a single unit (e.g., Replace -> Capitalize -> Decorate).
* **Undo Capability:** Functionality to dynamically remove specific decorators from a label instance.

### 4. Help Text Integration
* Support for attaching secondary "Help Text" to labels (RichLabel and CustomLabel) using the **Bridge Pattern**, separating the label's core abstraction from its help-text implementation.

### 5. Optimization
* **Flyweight Censor Factory:** Optimized creation of Censor transformations. It reuses instances for short words (length ≤ 4) to save memory, while creating new instances for longer words.

## Design Patterns Implemented

| Pattern | Usage in Project |
| :--- | :--- |
| **Strategy** | Encapsulates different text transformation algorithms (Capitalize, Trim, etc.), allowing them to be interchangeable within decorators. |
| **Decorator** | Allows dynamic addition of responsibilities (transformations) to Label objects without altering their class. |
| **Composite** | Treats a sequence of multiple transformations as a single transformation instance. |
| **Proxy** | Controls access to the "Custom Label," handling lazy initialization (reading from Input) and timeout logic. |
| **Bridge** | Decouples the `Label` abstraction from the `HelpText` implementation, allowing them to vary independently. |
| **Flyweight** | Efficiently manages memory by sharing `CensorTransformation` objects for frequently censored short words. |
| **Dependency Injection** | Used to assemble complex Label objects with various configurations interactively. |


## Label's Hierarchy
The diagram below shows the object-oriented class hierarchy
```
Label
├── SimpleLabel
│   └── RichLabel
├── HelpLabel
├── ProxyLabel
└── LabelDecorator
    ├── TextTransformationDecorator
    ├── CompositeTransformationDecorator
    ├── CyclingTransformationsDecorator
    └── RandomTransformationDecorator
```
