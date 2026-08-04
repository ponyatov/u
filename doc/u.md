# `μ`
## virtual cluster OS

(c) [[Dmitry Ponyatov]] <<dponyatov@gmail.com>> 2025 [[license/MIT|MIT]]

github: https://github.com/ponyatov/u

- bytecode/stack VM
	- [[compiler/AOT|AOT]] bytecode compiler
		- MCU-enabled ([[esp/ESP32|ESP32]], [[em/Cortex-M|Cortex-M]])
	- desktop/server host OSes ([[Linux/Linux|Linux]], [[Windows]], [[macOS]]?)
		- embedded Linux (RPi, PC104, retro devices)
- micro/embedded script engine
	- [[FORTH/FORTH|FORTH]]-inspired on-device [[lang/REPL|REPL]] (<64K SRAM)
- tiny portable [[git/gui|GUI]] ([[SDL/SDL|SDL]]-based, no host OS integration)
	- HMI (multimedia & IIoT, industrial control panels, SmartHome, CarPC,..)
- maybe...
	- WASM-based VM port to move parts of the virtualized infrastructure into the end-user browser to allow for low-latency and offline use cases

A virtual cluster based on a bytecode interpreter (without hardware virtualization) is a software-defined architecture where sandboxed bytecode runners share a unified runtime process. By bypassing hardware hypervisors, it eliminates the CPU and memory overhead of guest operating systems, using language-level isolation and async message-passing to act as a cluster of isolated actors.

## Core Architecture Components

- The Shared Runtime
	- A single native process (or tiny bare-metal kernel) running on each physical node. It manages raw memory, network sockets, and I/O routing without a traditional hypervisor layer.
- Software-Isolated Processes
	- Instead of VMs or containers, nodes in the virtual cluster are isolated code/memory spaces running within the runtime. Memory safety is strictly enforced by the bytecode isolation, meaning code cannot break out of its sandbox or access other tenants' data.
- Virtual Control Plane
	- An abstraction layer that makes these distributed bytecode runners look and behave like a multi-node cluster, scheduling workloads and routing cross-interpreter traffic.

## Similar approaches

- Inferno OS (Dis/Limbo)

- [[Erlang]] [[BEAM]] Virtual Machine
	- The gold standard for this architecture. The BEAM interpreter manages its own lightweight, independent processes, scheduling, garbage collection, and clustering natively over the network. It handles millions of virtual "nodes" with zero hardware virtualization.

- [[WebAssembly]] (Wasm) Clusters & [[WASI]]:
	- Modern decentralized micro-runtimes (like [[wasmtime]] or [[WAMR]]) use WebAssembly bytecode to build dense clusters. Frameworks like Fermyon Spin or [[Lunatic]] deploy hundreds of isolated Wasm instances across network nodes, treating the bytecode actors as a highly dense, hyper-scalable cluster.
		- [[Lunatic]] with [[people/Bernard Kolobara]]

- [[Java/Java|Java]] Virtual Machine ([[Java/JVM|JVM]]) Grid & Cluster Frameworks:
	- Ecosystems like Apache Ignite or Hazelcast build a virtualized distributed cluster directly on top of the JVM interpreter layer, clustering bytecode data objects and computing tasks seamlessly.

- Singularity (Historical Research OS)
	- A [[Microsoft Research]] operating system that replaced hardware-based page tables with software-isolated processes running type-safe MSIL bytecode.
