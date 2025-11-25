#set text(size: 15pt, font: ("Arial"))
#set heading(numbering: "1.")
#align(center)[#text(size: 25pt)[*1st LOGBOOK (2025-10-31)*]]
// LOGBOOK就是大家截至目前的一个工作的记录，图片、文字、各种形式都可以。
= Select the exact topic that I will work on 
There are six available topics according to my superior:
+ Energy-Efficient Communication Strategies for Distributed Agents Investigate how to minimize communication energy consumption without compromising information reliability in distributed agent networks.
+ Time-Triggered vs. Event-Triggered Communication in Control Systems Analyze the effectiveness of time-based versus event-based communication schemes in control performance for autonomous agents.
+ Scalable Control Algorithms for Large Agent Populations Develop control algorithms specifically optimized for scalability in large multi-agent environments with minimal communication overhead.
+ Impact of Communication Delay on Distributed Control Stability Examine how various levels of communication delay affect control system stability and propose mitigation strategies.
+ Priority-Based Communication Scheduling in Multi-Agent Systems Design a scheduling mechanism where agents prioritize messages based on control-critical information.
+ Information Compression Techniques for Control Data Exchange Explore data compression methods that maintain control accuracy while reducing communication load.
+ Fault-Tolerant Control under Partial Communication Loss Develop methods for maintaining control objectives even when some agents lose the ability to communicate.
+ AI Implications of Communication-Control Integration Investigate potential AI methods for joint communication-control mechanisms and propose design guidelines.

In the beginning, I conduct researches on all eight topics by searching 
information of relative books and papers, I found that the field 
that I am most interested and confident in is about compression algorithms.
Compared with other choices, I have learned some basic principles of
information theory and compression algorithms. And I am also engaged in 
designing a new open-source library of data compression in distributed 
control system. In conclusion, topic No.6 is the most suitable for me after preliminary investigation.
= Early stage research 
After selecting _Information Compression Techniques for Control Data Exchange_ as my primary research topic, I started with a thorough literature review on existing compression methods applied in distributed control and communication systems. The early research mainly focuses on three aspects:
+ Foundational Understanding:\
  I reviewed classical compression algorithms, including entropy coding (Huffman, Arithmetic), transform coding, and lightweight lossless algorithms like LZ77/LZ4, to understand their computational complexity and suitability for real-time control environments. In addition, I studied rate-distortion theory and its relevance to maintaining control accuracy under lossy compression.
+ Application in Control and Communication Systems:\
  Research papers on event-triggered communication and data-efficient control were analyzed to understand how information reduction can influence control stability and delay tolerance. I also examined recent works integrating compression with networked control systems (NCS) and edge computing frameworks.
+ Preliminary Experiments and Observations:\
  Using MATLAB and Python, I conducted initial experiments to compare the performance of different lightweight compression schemes (e.g., LZ4, Snappy, zlib) in transmitting control data. Results show that high compression ratios often increase latency, indicating a trade-off between communication efficiency and real-time response — an essential direction for further exploration.
= Determine my further working plans   
Based on the early-stage research, I have outlined several next steps for my future work:
-  October,2025
Select and analysis the topic and finish the primitive report 
-  November,2025
Analyze relative papers and learn deeply about the relevant study.
- December,2025
Attempt to optimize existing methods and manage to achieve satisfying results
- January,2025--June 2025
Writing project report while implement my theoretical research