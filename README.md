# Overview

This repository was started with the objective of holding a library that provides data structures and helper classes that would provide a dynamic allocation like environment to c++ codes that are forbiden to use dynamic allocation by the industries to which they belong. It is at the moment a personal space for exploration and inovation surrounding this subject.

# Contents

## Classes

### StackTemplate

#### Responsibility

This class provides a stack template that can be specialized to wichever class desired. It also allows for defining the maximum size of the stack at compilation time.

### MemoryProviderSingletonTemplate

#### Responsibility

This class is responsible for providing a dynamic allocation abstraction using static allocation underneath. By specializing MemoryProviderSingletonTemplate, it's possible to determine the maximum amount of memory positions it's going to provide and the class that those memory positions are going to hold.

All memory positions returned by the MemoryProviderSingletonTemplate are provided as shared pointers. The dealocation behavior of these shared pointers is overloaded to instead of dealocating the memory space, just making it available again through this class.
