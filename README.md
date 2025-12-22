# ABCUCourseLookup

<h1>Summary</h1>
This project is a command-line course lookup application written in C++, developed to demonstrate the practical use of data structures and algorithms. This course used a fictional education entity to engage in a real-world solutioning process.
This project highlights the ability to work with structured data, implement searching and sorting logic, and reasona bout performance trade-offs when selecting the appropriate data structure.

In the scenario the institution required an application capable of loading course data from a file and allowing users to interactively retrieve and view course information.

The application presents a CLI menu that allows the user to:
<ul>
  <li>Load course data from a file</li>
  <li>Display an alphanumeric list of all Computer Science courses</li>
  <li>Search for and display detaile dinformation about a specific course</li>
  <li>Exit the application</li>
</ul>

<h2>Contents:</h2>
<ul>
  <li>ProjectTwo.cpp</li>
</ul>

<h1>What Was Done Well</h1>
<p>Feedback from this project indicated the following was done well:</p>
<ol>
  <li><strong>Input - </strong> prompting for a filename, opening the file, trimming the fields, and normalizing course IDs and clear error messages for malformed records</li>
  <li><strong>Menu - </strong> requirements were implemented correctly: loop with numeric validation and exiting on option 9 while requiring data to be loaded before other actions</li>
  <li><strong>Loading Data Structure - </strong> the loader enforces required fields, uppercase IDs, clears previous data before reload, and continues safely bast bad lines</li>
  <li><strong>Course List - </strong> alphanumeric course ID sorting and printing each with its title</li>
  <li><strong>Course Information - </strong> ensuring lookup is case-insensitive and both prerequisite IDs with their titles are printed, clear not-found message, and the "Prerequisites: None" path is handled appropriately</li>
  <li><strong>Industry Standard Best Practices - </strong> including function decomposition, naming, and targeted error messages as well as validating menu input before conversion to int</li>
  
</ol>

<h1>What Could Be Improved</h1>
<p>Even though the project received a good score with great comments on implementation, there were some areas that garnered feedback where they could be improved:</p>
<ol>
  <li><strong>Input - </strong> Using >> for the filename is ok in this situation, but it won't allow for spaces</li>
  <ul>
    <li>In the future I probably should utilize std::getLine() as the >> (extraction) operator will stop reading a line once it encounters a space</li>
  </ul>
  <li><strong>Loading Data Structure - </strong> should consider detecting and reporting duplicate course IDs and unknown prerequisite references at load time</li>
  <ul>
    <li>While I can see this being situational, I can also see how having this report at load time is better for the end-user so they're aware right away</li>
  </ul>
  <li><strong>Course List - </strong> consider replacing the header with something like "Course List:" to better match the spec</li>
  <ul>
    <li>While this is project-specific, the concept is agnostic and I can see how this is better suited for user experience and readability</li>
  </ul>
  <li><strong>Industry Standard Best Practices - </strong> A few more brief comments above the helper functions and guiding STOI from potential overflow would strengthen robustness</li>
  <ul>
    <li>While I improved on best practices from my other courses, the theme of this feedback seems quite common - more comments</li>
  </ul>
</ol>

<h1>Challenges</h1>
The most challenging aspect of this project was selecting and implementing an appropriate data structure to balance performance and simplicity. The searching and sorting requirements forced me to carefully consider the complexities of time and program behavior as data scales.

Another challenge was ensuring that the file input formatting did not break prerequisite matching, which required trimming input tokens and validating relationships between courses.

While these challenges took time to figure a solution, they helped reinforce the importance of defining appropriate data structures in programming and engage in thoughtful data validation when working with external data sources.
