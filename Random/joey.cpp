### Detailed Development of the Admin Dashboard and Data Visualization Dashboard

#### 1. **Administrative Interface Development**

**Objective:**
To create a comprehensive and user-friendly administrative interface that allows efficient management of feedback data, services, and locations.

**Technologies Used:**
- **React:** A JavaScript library for building dynamic and responsive user interfaces.
- **Redux:** For state management, ensuring a seamless flow of data across the application.
- **Material-UI:** For designing a professional and consistent user interface.
- **Spring Boot:** For backend services to support the interface.
- **MySQL:** For storing and managing feedback data and other related information.

**Key Features:**
- **User Management:**
  - Administrators can create, edit, and delete user accounts.
  - Role-based access control allows different levels of permissions, ensuring security and proper access management.

- **Service and Location Management:**
  - Tools to add, edit, and remove services and locations within the system.
  - Bulk upload features for adding multiple services or locations simultaneously.
  - Search and filter capabilities to easily locate specific services or locations.

- **Feedback Data Management:**
  - Real-time access to feedback data collected through Qualtrics.
  - Advanced filtering options to view feedback based on various criteria such as date range, service category, or location.
  - Export options for downloading feedback data in various formats (CSV, Excel, PDF).

- **Reporting:**
  - Automated report generation based on selected parameters.
  - Customizable templates for generating detailed reports that can be used for presentations or further analysis.
  - Scheduled reports that can be automatically sent to specified email addresses at regular intervals.

- **Analytics and Insights:**
  - Built-in analytics tools to provide quick insights into feedback trends and patterns.
  - Visual representation of data through charts and graphs for easier interpretation.
  - Key performance indicators (KPIs) displayed on the dashboard for at-a-glance understanding of current performance.

**Development Process:**
1. **Requirement Gathering and Analysis:** Engaged with stakeholders to understand the specific needs and functionalities required from the administrative interface.
2. **Design and Prototyping:** Created detailed wireframes and prototypes using design tools like Figma to visualize the layout and user flow.
3. **Component Development:** Developed reusable React components for various parts of the interface, ensuring consistency and ease of maintenance.
4. **Backend Integration:** Connected the frontend with Spring Boot backend services to fetch, manipulate, and store data securely.
5. **Testing and Deployment:** Conducted thorough testing using Jest and React Testing Library for frontend, and JUnit for backend services. Deployed the application in stages to gather user feedback and make necessary improvements.

#### 2. **Data Visualization Dashboard Development**

**Objective:**
To develop a data visualization dashboard that provides upper-level management with actionable insights and a comprehensive view of key metrics.

**Technologies Used:**
- **React:** For building the dashboard interface.
- **D3.js and Chart.js:** For creating interactive and visually appealing data visualizations.
- **Redux:** For managing the state of the application.
- **RESTful APIs:** To fetch data from the backend services.
- **Spring Boot:** For backend services that aggregate and provide data to the frontend.

**Dashboard Features:**
- **Aggregate View:**
  - Provides a top-level overview at the department level, showing aggregated feedback data.
  - Visualizes overall performance metrics such as average feedback scores, total number of feedback entries, and general trends.

- **Drill-Down Capabilities:**
  - Allows users to click on high-level data points to drill down into more detailed views.
  - Users can navigate from department-level metrics to specific service or location details, and finally down to individual feedback entries.
  - This hierarchical view facilitates in-depth analysis and understanding of the feedback data.

- **Key Metrics Visualization:**
  - **Data Confidentiality:** Displays information on how feedback data is handled, ensuring compliance with data protection regulations.
  - **RTB (Run The Business):** Metrics related to the ongoing operations and how feedback impacts day-to-day business activities.
  - **CTB (Change The Business):** Insights into strategic initiatives and changes driven by feedback data.
  - **Priority Tickets:** Highlights critical feedback entries that require immediate attention and action.
  - **Risk Analysis:** Identifies potential risks based on feedback trends, enabling proactive measures.

- **User-Friendly Interface:**
  - Interactive charts and graphs that update in real-time based on user interactions.
  - Intuitive design that allows upper-level management to quickly access and interpret data.
  - Customizable dashboard layouts so users can prioritize and organize metrics according to their preferences.

- **Actionable Insights:**
  - Provides detailed insights into customer feedback, helping management identify areas of improvement.
  - Enables tracking of performance over time, facilitating strategic planning and decision-making.
  - Alerts and notifications for significant changes or patterns in feedback data, allowing for timely interventions.

**Development Process:**
1. **Requirement Gathering and Analysis:** Worked closely with upper-level management to identify the key metrics and insights needed for the dashboard.
2. **Design and Prototyping:** Developed detailed wireframes and interactive prototypes to visualize the user experience and gather feedback.
3. **Component Development:** Built reusable React components for various visualizations, ensuring a modular and scalable design.
4. **Data Integration:** Connected the dashboard to backend services using RESTful APIs to fetch and display real-time data.
5. **Testing and User Feedback:** Conducted extensive testing with tools like Jest for frontend components and Postman for API testing. Gathered user feedback to refine and improve the dashboard before final deployment.

### Conclusion

The development of the administrative interface and data visualization dashboard for the POY project has significantly enhanced the system's functionality, security, and usability. By providing administrators with powerful tools for data management and analysis, and offering upper-level management detailed insights through interactive visualizations, the project ensures efficient feedback handling and informed decision-making. This comprehensive approach will contribute to better service quality and customer satisfaction across multiple industries.


// GridComponent.js
import React, { useState } from 'react';
import { AgGridReact } from 'ag-grid-react';
import 'ag-grid-community/styles/ag-grid.css';
import 'ag-grid-community/styles/ag-theme-alpine.css';
import SymbolDropdownRenderer from './SymbolDropdownRenderer'; // Adjust the import path as needed

const GridComponent = () => {
  const [rowData] = useState([
    { symbol: 'symbol1', value: '10' },
    { symbol: 'symbol2', value: '20' },
  ]);

  const symbols = ['symbol1', 'symbol2', 'symbol3']; // Your list of symbols

  const [columnDefs] = useState([
    {
      headerName: 'Symbol',
      field: 'symbol',
      cellRendererFramework: (params) => <SymbolDropdownRenderer {...params} symbols={symbols} />,
    },
    { headerName: 'Value', field: 'value' },
  ]);

  return (
    <div className="ag-theme-alpine" style={{ height: 400, width: 600 }}>
      <AgGridReact
        rowData={rowData}
        columnDefs={columnDefs}
      />
    </div>
  );
};

export default GridComponent;



// SymbolDropdown.js
import React, { useState, useEffect } from 'react';
import Select from 'react-select';
import './SymbolDropdown.css';

const SymbolDropdown = ({ symbols, onSymbolChange, initialValue }) => {
  const [selectedOption, setSelectedOption] = useState(null);

  useEffect(() => {
    if (initialValue) {
      setSelectedOption({ value: initialValue, label: initialValue });
    }
  }, [initialValue]);

  const handleChange = (selectedOption) => {
    setSelectedOption(selectedOption);
    onSymbolChange(selectedOption ? selectedOption.value : null);
  };

  const options = symbols.map(id => ({ value: id, label: id }));

  return (
    <Select
      options={options}
      value={selectedOption}
      onChange={handleChange}
      placeholder="Search and select a symbol..."
      isClearable
    />
  );
};

export default SymbolDropdown;


// SymbolDropdownRenderer.js
import React, { useState, useEffect } from 'react';
import SymbolDropdown from './SymbolDropdown'; // Adjust the import path as needed

const SymbolDropdownRenderer = (props) => {
  const [value, setValue] = useState(props.value);

  useEffect(() => {
    setValue(props.value);
  }, [props.value]);

  const handleSymbolChange = (symbol) => {
    setValue(symbol);
    props.node.setDataValue(props.colDef.field, symbol); // Update the grid data
    props.api.stopEditing(); // Stop editing when a symbol is selected
  };

  return (
    <SymbolDropdown
      symbols={props.symbols}
      onSymbolChange={handleSymbolChange}
      initialValue={value}
    />
  );
};

export default SymbolDropdownRenderer;


// SymbolDropdownRenderer.js
import React, { useEffect, useState } from 'react';
import SymbolDropdown from './SymbolDropdown'; // Adjust the import path as needed

const SymbolDropdownRenderer = (props) => {
  const [value, setValue] = useState(props.value);

  // Updates the state with the selected symbol
  const handleSymbolChange = (symbol) => {
    setValue(symbol);
    props.node.setDataValue(props.colDef.field, symbol); // Update the grid data
  };

  return (
    <SymbolDropdown onSymbolChange={handleSymbolChange} />
  );
};

export default SymbolDropdownRenderer;




const customStyles = {
    option: (provided, state) => ({
      ...provided,
      display: 'flex',
      alignItems: 'center',
      backgroundColor: state.isFocused ? 'white' : 'white', // Prevent background change on hover
      color: 'black', // Ensure text color remains consistent
      padding: 10, // Optional: Adjust padding for better spacing
      cursor: 'default', // Set cursor to default
    }),
    singleValue: (provided) => ({
      ...provided,
      display: 'flex',
      alignItems: 'center',
    }),
  };


/* src/components/SymbolDropdown.css */
.custom-option {
  display: flex;
  align-items: center;
}

.custom-option .option-icon {
  width: 24px;
  height: 24px;
  margin-right: 10px;
}

.symbol-preview {
  display: flex;
  align-items: center;
  margin-top: 10px;
}

.symbol-preview svg {
  width: 32px;
  height: 32px;
  margin-right: 10px;
}



// src/components/SymbolDropdown.js
import React, { useState, useEffect } from 'react';
import Select from 'react-select';
import './SymbolDropdown.css';  // Import CSS for styling the SVG display if needed

const SymbolDropdown = () => {
  const [symbols, setSymbols] = useState([]);
  const [options, setOptions] = useState([]);
  const [selectedSymbol, setSelectedSymbol] = useState(null);

  useEffect(() => {
    const fetchSymbols = async () => {
      const response = await fetch('/symbols.html');
      const text = await response.text();
      const parser = new DOMParser();
      const doc = parser.parseFromString(text, 'text/html');
      const symbolElements = doc.querySelectorAll('symbol');
      const symbolIds = Array.from(symbolElements).map(symbol => symbol.id);
      setSymbols(symbolIds);
      setOptions(symbolIds.map(id => ({ value: id, label: id })));
    };

    fetchSymbols();
  }, []);

  const handleChange = (selectedOption) => {
    setSelectedSymbol(selectedOption ? selectedOption.value : null);
  };

  // Custom Option component
  const CustomOption = ({ innerRef, innerProps, data }) => (
    <div ref={innerRef} {...innerProps} className="custom-option">
      <svg className="option-icon">
        <use xlinkHref={`#${data.value}`} />
      </svg>
      {data.label}
    </div>
  );

  return (
    <div>
      <Select
        options={options}
        onChange={handleChange}
        placeholder="Search and select a symbol..."
        isClearable
        components={{ Option: CustomOption }}
      />
      {selectedSymbol && (
        <div className="symbol-preview">
          <svg>
            <use xlinkHref={`#${selectedSymbol}`} />
          </svg>
          <span>{selectedSymbol}</span>
        </div>
      )}
    </div>
  );
};

export default SymbolDropdown;





/* src/components/SymbolDropdown.css */
.symbol-preview {
  display: flex;
  align-items: center;
  margin-top: 10px;
}

.symbol-preview svg {
  width: 32px;
  height: 32px;
  margin-right: 10px;
}


// src/components/SymbolDropdown.js
import React, { useState, useEffect } from 'react';
import Select from 'react-select';
import './SymbolDropdown.css';  // Import CSS for styling the SVG display if needed

const SymbolDropdown = () => {
  const [symbols, setSymbols] = useState([]);
  const [options, setOptions] = useState([]);
  const [selectedSymbol, setSelectedSymbol] = useState(null);

  useEffect(() => {
    const fetchSymbols = async () => {
      const response = await fetch('/symbols.html');
      const text = await response.text();
      const parser = new DOMParser();
      const doc = parser.parseFromString(text, 'text/html');
      const symbolElements = doc.querySelectorAll('symbol');
      const symbolIds = Array.from(symbolElements).map(symbol => symbol.id);
      setSymbols(symbolIds);
      setOptions(symbolIds.map(id => ({ value: id, label: id })));
    };

    fetchSymbols();
  }, []);

  const handleChange = (selectedOption) => {
    setSelectedSymbol(selectedOption ? selectedOption.value : null);
  };

  return (
    <div>
      <Select
        options={options}
        onChange={handleChange}
        placeholder="Search and select a symbol..."
        isClearable
      />
      {selectedSymbol && (
        <div className="symbol-preview">
          <svg>
            <use xlinkHref={`#${selectedSymbol}`} />
          </svg>
          <span>{selectedSymbol}</span>
        </div>
      )}
    </div>
  );
};

export default SymbolDropdown;

// src/components/SymbolDropdown.js
import React, { useState, useEffect } from 'react';

const SymbolDropdown = () => {
  const [searchTerm, setSearchTerm] = useState('');
  const [symbols, setSymbols] = useState([]);
  const [filteredSymbols, setFilteredSymbols] = useState([]);
  const [selectedSymbol, setSelectedSymbol] = useState('');

  useEffect(() => {
    const fetchSymbols = async () => {
      const response = await fetch('/symbols.html');
      const text = await response.text();
      const parser = new DOMParser();
      const doc = parser.parseFromString(text, 'text/html');
      const symbolElements = doc.querySelectorAll('symbol');
      const symbolIds = Array.from(symbolElements).map(symbol => symbol.id);
      setSymbols(symbolIds);
      setFilteredSymbols(symbolIds);
    };

    fetchSymbols();
  }, []);

  useEffect(() => {
    setFilteredSymbols(
      symbols.filter(symbol =>
        symbol.toLowerCase().includes(searchTerm.toLowerCase())
      )
    );
  }, [searchTerm, symbols]);

  const handleSelectChange = (e) => {
    setSelectedSymbol(e.target.value);
  };

  return (
    <div>
      <input
        type="text"
        placeholder="Search symbols..."
        value={searchTerm}
        onChange={(e) => setSearchTerm(e.target.value)}
      />
      <select value={selectedSymbol} onChange={handleSelectChange}>
        <option value="">Select a symbol</option>
        {filteredSymbols.map((symbol) => (
          <option key={symbol} value={symbol}>
            {symbol}
          </option>
        ))}
      </select>
      {selectedSymbol && (
        <div>
          <svg>
            <use xlinkHref={`#${selectedSymbol}`} />
          </svg>
        </div>
      )}
    </div>
  );
};

export default SymbolDropdown;

// src/components/SymbolDropdown.js
import React, { useState, useEffect } from 'react';

const SymbolDropdown = () => {
  const [searchTerm, setSearchTerm] = useState('');
  const [symbols, setSymbols] = useState([]);
  const [filteredSymbols, setFilteredSymbols] = useState([]);

  useEffect(() => {
    const fetchSymbols = async () => {
      const response = await fetch('/symbols.svg');
      const text = await response.text();
      const parser = new DOMParser();
      const svgDoc = parser.parseFromString(text, 'image/svg+xml');
      const symbolElements = svgDoc.querySelectorAll('symbol');
      const symbolIds = Array.from(symbolElements).map(symbol => symbol.id);
      setSymbols(symbolIds);
      setFilteredSymbols(symbolIds);
    };

    fetchSymbols();
  }, []);

  useEffect(() => {
    setFilteredSymbols(
      symbols.filter(symbol =>
        symbol.toLowerCase().includes(searchTerm.toLowerCase())
      )
    );
  }, [searchTerm, symbols]);

  return (
    <div>
      <input
        type="text"
        placeholder="Search symbols..."
        value={searchTerm}
        onChange={(e) => setSearchTerm(e.target.value)}
      />
      <ul>
        {filteredSymbols.map((symbol) => (
          <li key={symbol}>
            <svg>
              <use xlinkHref={`#${symbol}`} />
            </svg>
            {symbol}
          </li>
        ))}
      </ul>
    </div>
  );
};

export default SymbolDropdown;



// src/App.js
import React from 'react';
import SymbolDropdown from './components/SymbolDropdown';

const App = () => {
  return (
    <div className="App">
      <h1>Searchable SVG Symbol Dropdown</h1>
      <SymbolDropdown />
    </div>
  );
};

export default App;




import React, { useState, useEffect } from 'react';

function SvgDropdown() {
  const [symbols, setSymbols] = useState([]);
  const [selectedSymbol, setSelectedSymbol] = useState(null);
  const [searchTerm, setSearchTerm] = useState('');

  useEffect(() => {
    const fetchSvgSymbols = async () => {
      try {
        const response = await fetch('path/to/your/svg/file.html');
        const html = await response.text();
        const parser = new DOMParser();
        const doc = parser.parseFromString(html, 'text/html');
        const svg = doc.querySelector('svg');

        if (svg) {
          const svgSymbols = Array.from(svg.querySelectorAll('symbol'));
          const symbolData = svgSymbols.map((symbol) => ({
            id: symbol.getAttribute('id'),
          }));
          setSymbols(symbolData);
        }
      } catch (error) {
        console.error('Error fetching SVG symbols:', error);
      }
    };

    fetchSvgSymbols();
  }, []);

  const handleSymbolSelect = (symbol) => {
    setSelectedSymbol(symbol);
  };

  const filteredSymbols = symbols.filter((symbol) =>
    symbol.id.toLowerCase().includes(searchTerm.toLowerCase())
  );

  return (
    <div>
      <input
        type="text"
        placeholder="Search symbols"
        value={searchTerm}
        onChange={(e) => setSearchTerm(e.target.value)}
      />
      <select onChange={(e) => handleSymbolSelect(e.target.value)}>
        <option value="">Select a symbol</option>
        {filteredSymbols.map((symbol) => (
          <option key={symbol.id} value={symbol.id}>
            {symbol.id}
          </option>
        ))}
      </select>
      <div>
        {selectedSymbol && (
          <svg>
            <use xlinkHref={`#${selectedSymbol.id}`} />
          </svg>
        )}
      </div>
    </div>
  );
}

export default SvgDropdown;

import React, { useState } from 'react';

function SvgDropdown({ symbols }) {
  const [selectedSymbol, setSelectedSymbol] = useState(null);
  const [searchTerm, setSearchTerm] = useState('');

  const handleSymbolSelect = (symbol) => {
    setSelectedSymbol(symbol);
  };

  const filteredSymbols = symbols.filter((symbol) =>
    symbol.id.toLowerCase().includes(searchTerm.toLowerCase())
  );

  return (
    <div>
      <input
        type="text"
        placeholder="Search symbols"
        value={searchTerm}
        onChange={(e) => setSearchTerm(e.target.value)}
      />
      <select onChange={(e) => handleSymbolSelect(e.target.value)}>
        <option value="">Select a symbol</option>
        {filteredSymbols.map((symbol) => (
          <option key={symbol.id} value={symbol.id}>
            {symbol.id}
          </option>
        ))}
      </select>
      <div>
        {selectedSymbol && (
          <svg>
            <use xlinkHref={`#${selectedSymbol.id}`} />
          </svg>
        )}
      </div>
    </div>
  );
}

export default SvgDropdown;

// server.js
const express = require('express');
const multer = require('multer');
const path = require('path');
const fs = require('fs');

const app = express();
const port = 5000;

// Set up multer for handling file uploads
const storage = multer.diskStorage({
  destination: function (req, file, cb) {
    cb(null, 'uploads/'); // Specify the directory where files will be stored
  },
  filename: function (req, file, cb) {
    cb(null, file.originalname); // Keep the original file name
  }
});

const upload = multer({ storage: storage });

// Route to handle file upload
app.post('/upload', upload.single('file'), (req, res) => {
  // File has been uploaded successfully
  res.sendStatus(200);
});

// Route to handle file download
app.get('/download/:filename', (req, res) => {
  const filename = req.params.filename;
  const filePath = path.join(__dirname, 'uploads', filename);

  fs.access(filePath, fs.constants.F_OK, (err) => {
    if (err) {
      // File does not exist
      return res.status(404).send('File not found');
    }

    // Stream the file to the client
    const fileStream = fs.createReadStream(filePath);
    fileStream.pipe(res);
  });
});

// Serve uploaded files statically
app.use(express.static('uploads'));

// Start the server
app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});


// FileUploader.js
import React, { useState } from 'react';
import axios from 'axios';

const FileUploader = () => {
  const [file, setFile] = useState(null);

  const handleFileUpload = (event) => {
    const uploadedFile = event.target.files[0];
    setFile(uploadedFile);
  };

  const handleSubmit = async () => {
    if (file) {
      try {
        const formData = new FormData();
        formData.append('file', file);

        await axios.post('http://localhost:5000/upload', formData, {
          headers: {
            'Content-Type': 'multipart/form-data'
          }
        });

        alert('File uploaded successfully!');
      } catch (error) {
        console.error('Error uploading file:', error);
        alert('Failed to upload file');
      }
    } else {
      alert("Please upload a file before submitting.");
    }
  };

  return (
    <div>
      <h2>File Uploader</h2>
      <input type="file" onChange={handleFileUpload} />
      <button onClick={handleSubmit}>Submit</button>
    </div>
  );
};

export default FileUploader;




const express = require('express');
const multer  = require('multer');
const path = require('path');

const app = express();

// Set up multer for handling file uploads
const storage = multer.diskStorage({
  destination: function (req, file, cb) {
    cb(null, 'uploads/'); // Specify the directory where files will be stored
  },
  filename: function (req, file, cb) {
    cb(null, file.originalname); // Keep the original file name
  }
});

const upload = multer({ storage: storage });

// Route to handle file upload
app.post('/upload', upload.single('file'), (req, res) => {
  // File has been uploaded successfully
  res.sendStatus(200);
});

// Serve uploaded files statically
app.use(express.static('uploads'));

// Start the server
const port = 3000;
app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});



import React, { useState } from 'react';

const FileUploader = () => {
  const [file, setFile] = useState(null);

  // Function to handle file upload
  const handleFileUpload = (event) => {
    const uploadedFile = event.target.files[0];
    setFile(uploadedFile);
  };

  // Function to handle form submission
  const handleSubmit = async () => {
    if (file) {
      // Create a FormData object and append the file to it
      const formData = new FormData();
      formData.append('file', file);

      try {
        // Send the file to your server
        const response = await fetch('/upload', {
          method: 'POST',
          body: formData,
        });
        if (response.ok) {
          alert('File uploaded successfully!');
        } else {
          throw new Error('Failed to upload file');
        }
      } catch (error) {
        console.error('Error uploading file:', error);
        alert('Failed to upload file');
      }
    } else {
      alert("Please upload a file before submitting.");
    }
  };

  return (
    <div>
      <h2>File Uploader</h2>
      <input type="file" onChange={handleFileUpload} />
      <button onClick={handleSubmit}>Submit</button>
    </div>
  );
};

export default FileUploader;



import React, { useState } from 'react';

const FileUploader = () => {
  const [file, setFile] = useState(null);

  // Function to handle file upload
  const handleFileUpload = (event) => {
    const uploadedFile = event.target.files[0];
    setFile(uploadedFile);
  };

  // Function to handle form submission
  const handleSubmit = () => {
    if (file) {
      // Save the file to a specified location
      saveFileLocally(file);
    } else {
      alert("Please upload a file before submitting.");
    }
  };

  // Function to save the file locally
  const saveFileLocally = (file) => {
    // Your logic to save the file locally goes here
    // For example, you can use File API to save the file
    // Here's a basic example using File Reader:
    const reader = new FileReader();
    reader.onload = (e) => {
      const content = e.target.result;
      // Save 'content' to a specified local location
      console.log("File content:", content);
      alert("File saved locally!");
    };
    reader.readAsText(file);
  };

  return (
    <div>
      <h2>File Uploader</h2>
      <input type="file" onChange={handleFileUpload} />
      <button onClick={handleSubmit}>Submit</button>
    </div>
  );
};

export default FileUploader;




import React, { useState, useEffect } from 'react';

const Dropdown = () => {
  const [imageOptions, setImageOptions] = useState([]);

  useEffect(() => {
    const fetchImages = async () => {
      try {
        // Fetch HTML file containing SVG image sources
        const response = await fetch('images.html');
        const html = await response.text();

        // Parse HTML to extract SVG elements and their titles
        const parser = new DOMParser();
        const doc = parser.parseFromString(html, 'text/html');
        const svgs = Array.from(doc.querySelectorAll('svg'));

        // Extract titles of SVG images
        const options = svgs.map(svg => ({
          value: svg.getAttribute('title'),
          label: svg.getAttribute('title')
        }));

        // Set image options state
        setImageOptions(options);
      } catch (error) {
        console.error('Error fetching or parsing HTML:', error);
      }
    };

    // Call fetchImages function
    fetchImages();
  }, []);

  return (
    <div>
      <select id="imageDropdown">
        <option value="">Select Image</option>
        {imageOptions.map(option => (
          <option key={option.value} value={option.value}>
            {option.label}
          </option>
        ))}
      </select>
    </div>
  );
};

export default Dropdown;
// App.js// Function to fetch HTML file, parse it, and populate dropdown with SVG images and titles
const populateDropdown = async () => {
  try {
    // Fetch HTML file containing SVG image sources
    const response = await fetch('images.html');
    const html = await response.text();

    // Parse HTML to extract SVG elements and their titles
    const parser = new DOMParser();
    const doc = parser.parseFromString(html, 'text/html');
    const svgs = Array.from(doc.querySelectorAll('svg'));

    // Create dropdown select element
    const dropdown = document.createElement('select');
    dropdown.id = 'imageDropdown';
    dropdown.innerHTML = '<option value="">Select Image</option>';

    // Populate dropdown with SVG image data
    svgs.forEach(svg => {
      const option = document.createElement('option');
      const title = svg.getAttribute('title');
      option.value = title;
      option.text = title;
      dropdown.appendChild(option);
    });

    // Append dropdown to a container
    const dropdownContainer = document.createElement('div');
    dropdownContainer.id = 'dropdownContainer';
    dropdownContainer.appendChild(dropdown);

    // Append container to the document body
    document.body.appendChild(dropdownContainer);
  } catch (error) {
    console.error('Error fetching or parsing HTML:', error);
  }
};

// Call function to populate and render dropdown when page loads
window.onload = () => {
  populateDropdown();
};


import React, { useState } from 'react';
import { Navbar, NavbarBrand, Nav, NavItem, NavLink, Container, Row, Col } from 'reactstrap';
import Sidebar from './Sidebar';

function App() {
  const [isOpen, setIsOpen] = useState(false);

  const toggleSidebar = () => {
    setIsOpen(!isOpen);
  };

  return (
    <div>
      <Navbar color="light" light expand="md">
        <NavbarBrand href="/">Your Logo</NavbarBrand>
        <Nav className="mr-auto" navbar>
          <NavItem>
            <NavLink href="/components/">Components</NavLink>
          </NavItem>
          <NavItem>
            <NavLink href="https://github.com/reactstrap/reactstrap">GitHub</NavLink>
          </NavItem>
        </Nav>
      </Navbar>
      <Container fluid>
        <Row>
          <Col xs="3">
            <Sidebar isOpen={isOpen} toggleSidebar={toggleSidebar} />
          </Col>
          <Col xs="9">
            <h1>Main Content</h1>
          </Col>
        </Row>
      </Container>
    </div>
  );
}

export default App;




// Sidebar.js

import React from 'react';
import { Collapse, Nav, NavItem, NavLink } from 'reactstrap';

const Sidebar = ({ isOpen, toggleSidebar }) => {
  return (
    <Collapse isOpen={isOpen}>
      <Nav vertical>
        <NavItem>
          <NavLink href="#" onClick={toggleSidebar}>Link 1</NavLink>
        </NavItem>
        <NavItem>
          <NavLink href="#" onClick={toggleSidebar}>Link 2</NavLink>
        </NavItem>
        <NavItem>
          <NavLink href="#" onClick={toggleSidebar}>Link 3</NavLink>
        </NavItem>
      </Nav>
    </Collapse>
  );
};

export default Sidebar;
