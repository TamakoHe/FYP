#set heading(numbering: "1.")
#import "@preview/wrap-it:0.1.1": wrap-content
#set text(font: "Arial")
#let t1=text(size: 22pt, font: "Arial")[Glasgow College, UESTC]
#let f1=image("image.png", width: 50%)
#wrap-content(f1,t1, align: right)
#set text(size: 15pt, font: "Arial")

*Project Specifications and Preliminary Report on UESTC4006P(BEng) Final Year Project	
*

#strong[Please start by saving this file with the name:]
GUID\_Surname\_UESTC4006P\_Preliminary\_year

#emph[#strong[\*\*\*\* Please add appropriate course code]]

#figure(
  align(center)[#table(
    columns: (19.97%, 18.93%, 19.79%, 41.31%),
    align: (left,left,left,left,),
    table.header(table.cell(align: left)[Student
      Name], table.cell(align: left)[He WenXiao], table.cell(align: left)[Placement
      Company

      \(if appropriate)

      ], table.cell(align: left)[],),
    table.hline(),
    table.cell(align: left)[Student Matriculation
    Number], table.cell(align: left)[2839915H], table.cell(align: left)[Working
    Title of Project], table.cell(align: left)[Data compression algorithms in joint communication and control systems design],
    table.cell(align: left)[UESTC Student
    Number], table.cell(align: left)[20221905\ 04031], table.cell(align: left)[Name of
    First Supervisor], table.cell(align: left)[Olaoluwa Popoola],
    table.cell(align: left)[Degree
    programme], table.cell(align: left)[Final Year Project], table.cell(align: left, rowspan: 2)[#strong[Declaration
    of Originality and Submission
    Information]], table.cell(rowspan: 2)[#emph[I affirm that this
    submission is all my own work in accordance with the University of
    Glasgow and UESTC Regulations, and the James Watt School of
    Engineering requirements.]

    Signed (Student):
  He WenXiao
    ],
    table.cell(align: left)[Academic year], table.cell(align: left)[Year 4],
  )]
  , kind: table
  )

#strong[Your report should be NO more than 8 pages in length and include
the below subject headings and incorporated within this document:]

#strong[Project Description] (no more than half a page)

#strong[Measurable Outcomes] (no more than half a page): including Main
Tasks and Targets, and Tangible outcomes (Hardware, Software, Hardware &
Software, Theoretical research)

#strong[Technical Background] (at least four pages)#strong[:] including
Literature Review, Topic Basis and Significance, and Research Status and
Development Trend

#strong[References]

#strong[Work Plan] (no more than one page): including Project Outline

#strong[Resources:] Complete the component request form and email the
form to your 1#super[st] supervisor separately.

#strong[Rist Assessment Form:] You must submit a Risk Assessment Form.
Please have it signed with your 1#super[st] supervisor.

#strong[Deadlines for submission of this report:] Please upload this
report via the Moodle page and GC-UESTC FYP management system by the
deadline mentioned in Table 1 of your project handbook.
= Project Description
This project focuese on designing, implementing, and evaluating a lightweight information compression framework for control data exchanged between distributed agents in a simulated environment.
It is required to model a small network of communication agents such as robots and sensors with control-related messages 
compressed by certain algorithm aiming to develop and evaluate data compression techniques which can effectively reduce 
communication load in distributed control systems while maintaining stable and accurate system performance.
= Measurable Outcomes 
== Main Tasks
+ Learn the basic principles of existing compression algorithms
+ Conduct simulation of distributed operation and exam existing algorithms
+ Analysis potential optimizations techniques
+ Implement and conduct experiments on potential improvement
+ Evaluate the results and finish the report
== Targets 
+ Improved compression rate compared to existing algorithms
+ Increased compression speed compared to existing algorithms
+ Reduced computation consuming compared to existing algorithms
+ Improved control accuracy and system responsiveness compared to existing algorithms
== Tangible Outcomes 
+ Working simulation model of a distributed multi-agent control system with communication links.
+ An effective distrusted control platform that utilizes the proposed compression method
+ A demonstration in industrial application that consisting of distributed agents connected with optimized compression algorithm  
= Technical Background
Limited bandwidth, intermittent connectivity, latency, and energy restrictions are major constraints of distributed control systems and 
multi-agent systems. These limitations make it essential to compress 
control-relevant data without degrading relevant performance.
This section surveys the theoretical foundations, principal compression
algorithm and realistic challenges in distributed control and joint 
communication-control (JCC) design. 
== Theoretical foundations: information, rate and control performance
The control performance and the amount of 
communicated information is strongly connected. Early work---often called the data-rate theorem---framing stabilizability as a function 
of information rate. Tools based on information-theoretic tools such as 
rate-distortion theory have been adapted to pose trade-offs between 
bit rate and control cost (e.g., control accuracy and system responsiveness).
== Classic discrete methods: quantization and entropy coding @QFS
The most direct compression tool in control systems is quantization.
Uniform and nonuniform quantizers, dynamic/adaptive quantization schemes,
and logarithmic scalar quantizers have been explored for state and control signal compression. Controllers and observers can be designed 
to tolerate quantization error through robust control techniques, state 
bounds, and occasional resynchronization. Entropy coding such as Huffman,
arithmetic coding can be combined with quantization to exploit distributional structure and reduce average bit rate further. Key pratical considerations include encoder-decoder synchronization, bounded
round-off error, and packetization for variable---length codes.
== Event-triggered and self-triggered communication
Event-triggered control (ETC) shifts from regular sampling to sending 
updates only when a specific condition, such as an estimation or tracking error surpassing a threshold, is met. This reduces 
communication frequency while maintaining performance, effectively compressing data transmission.
Self-triggered schemes precalculate the next transmission time, eliminating the need for constant monitoring. ETC can integrate with 
quantization and prioritized messaging, allocating more bits to critical 
updates. Research includes stability analyses under various triggering 
rules, robustness against delays and packet losses, and techniques for
tuning triggers to balance communication rate and performance.
== Sparse representations and compressed sensing @SPC
Compressed sensing and sparse modeling exploit the fact that many
control signals (or their derivatives/representations) are compressible 
in an appropriate basis. By transmitting a small number of random projections or sparse coefficient indices, the receving node can reconstruct a close approximate of the state or control vector. 
In distributed settings, sparsity can be enforced at the agent level (sparse control actions) or in a transform domain. Compressed sensing techniques are attractive for high-dimensional systems and sensor networks, but require careful design of measurement matrices, reconstruction algorithms (often iterative), and analysis of reconstruction error impact on closed-loop stability.
== Task-oriented and control-aware compression @TOD
Rather than minimizing conventional signal distortion, task-oriented compression explicitly optimizes the representation for the downstream control objective. Examples include minimizing closed-loop cost or estimation error directly in the compression loss function. This perspective leads to rate–cost optimization problems where the “distortion” is replaced by control loss. Control-aware quantizers, prioritized encoding of control-critical state components, and selective fidelity allocation across state dimensions are practical instantiations. These methods can significantly outperform generic source compression when the control task imposes structure on what information is essential.
== Learning-based and end-to-end approaches
Recent trends leverage machine learning to learn compact 
representations tailored to control tasks. Autoencoders, variational autoencoders, and neural compressors can be trained end-to-end to generate low-dimensional messages that maintain control performance. In multi-agent systems, learned encoders capture interaction patterns and distill them into task-relevant embeddings.

*Advantages*: adaptability to nonlinear dynamics and complex observation models.

*Drawbacks*: need for extensive training data, challenges in formal guarantees, and concerns over generalization and robustness.
== Joint design and co-optimization with communication
It is essential to combine compression strategies and control laws.
For example, co-design of event triggers and quantizers, or optimization 
of control policies. These formulations allow trade-offs to be allocated 
optimally. Game-theoretic and other optimization methods can be 
used to handle decentralized decision-making in networks where agents balance local control performance and global communication resources.
== Practical constraints and robustness issues
Real-world factors including variable latency, packet loss and channel noise complicate idealized compression designs. Therefore, robustness analyses must consider possible worst casesand provide bounded-error guarantees. Additionally, variable-length or probabilistic compressors complicate timing analysis in hard real-time systems. Security and privacy concerns arise when compressed messages expose sensitive state information; encryption and privacy-preserving compression introduce additional trade-offs.
== Open problems and research gaps @OSPT @DRP
+ *Bridging theory and practice*: Many existing theories about information compression and control are based on ideal or simplified models. Applying these ideas to real-world systems — which are often nonlinear, time-varying, and involve many interacting agents — is still a big challenge.
+ *Delay and packet loss*: In real wireless networks, data can be delayed or lost during transmission. Figuring out how to design compression methods that still keep the control system stable and reliable under such conditions is not yet well studied, especially for learning-based compression methods.
+ *Verifiable learning-based compressors*: Neural network compressors can achieve excellent performance, but they often lack formal guarantees of stability and safety. For safety-critical systems like drones or autonomous vehicles, being able to prove that the system will remain safe is essential.
+ *Distributed compression under coordination*: In multi-agent systems, multiple agents need to share information and work together. Designing compression protocols that allow them to communicate efficiently, protect privacy, and still coordinate effectively is an emerging and difficult research problem.
+ *Resource-aware co-design*: Real systems must balance many factors — control accuracy, energy use, computation time, delay, and bandwidth. Creating tools that can optimize all these factors together is still an open challenge, and current solutions are far from complete.
= References
#bibliography("ref.bib")
= Work Plan
== October,2025
Select and analysis the topic and finish the primitive report 
== November,2025
Analyze relative papers and learn deeply about the relevant study.
== December,2025
Attempt to optimize existing methods and manage to achieve satisfying results
== January,2025--June 2025
Writing project report while implement my theoretical research
= Resources
+ Software systems that can simulate industrial production with multi agents where Joint Communication and Control (JCC) is required.
+ High Performance Computation servers which can accelerate the simulation speed and handling capacity
+ A physical virtualization environment which serve as a demonstration of my proposed compression method
= Risk Assessment Form

#figure(caption: [Risk Assessment Form])[#table(align: center, columns: 5)[Num][Hazard][Possible Harm][Risk Level][Control/Action][1][*System Overcharge or Server Crash*][Data loss or experiment interruption][Medium][Regularly back up experimental data and monitor system's status][2][*Network Delay or Communication Failure*][Agent disconnection or degraded control performance][High][mplement fault-tolerant communication, use local buffering, and enable automatic reconnection][3][*Software or Configuration Error*][Simulation instability or inaccurate results.
][Medium][Apply version control (Git), perform parameter verification, and conduct unit testing]]
