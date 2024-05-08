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
