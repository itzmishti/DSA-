<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Employee Access</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
            background-color: #f0f0f0;
        }

        .container {
            background-color: #ffffff;
            border-radius: 8px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
            width: 90%;
            max-width: 400px;
            animation: fadeIn 1s ease-in-out;
            overflow: hidden;
        }

        @keyframes fadeIn {
            from { opacity: 0; }
            to { opacity: 1; }
        }

        .top-bar {
            background-color: #007bff;
            color: white;
            padding: 15px;
            text-align: center;
            font-size: 24px;
            font-weight: bold;
            width: 100%;
            box-sizing: border-box;
            animation: slideIn 1s ease-in-out;
        }

        @keyframes slideIn {
            from { transform: translateY(-100%); }
            to { transform: translateY(0); }
        }

        .content {
            padding: 20px;
            box-sizing: border-box;
        }

        .input-group {
            margin-bottom: 15px;
        }

        .input-group label {
            display: block;
            margin-bottom: 5px;
            font-weight: bold;
        }

        .input-group input {
            width: calc(100% - 10px);
            padding: 8px;
            border: 1px solid #ccc;
            border-radius: 4px;
            margin-right: 10px;
        }

        .input-group-buttons {
            display: flex;
            justify-content: space-between;
            margin-bottom: 15px;
        }

        .input-group-buttons button {
            width: 48%;
            padding: 10px;
            background-color: #007bff;
            color: white;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            font-size: 16px;
        }

        .input-group-buttons button:hover {
            background-color: #0056b3;
        }

        .message {
            margin-top: 20px;
            padding: 10px;
            border-radius: 4px;
            display: none;
        }

        .message.success {
            background-color: #d4edda;
            color: #155724;
        }

        .message.error {
            background-color: #f8d7da;
            color: #721c24;
        }

        .verify-next {
            display: none;
            text-align: center;
            margin-top: 20px;
        }

        .verify-next button {
            padding: 10px 20px;
            background-color: #007bff;
            color: white;
            border: none;
            border-radius: 4px;
            cursor: pointer;
            font-size: 16px;
        }

        .verify-next button:hover {
            background-color: #0056b3;
        }

        .spacer {
            height: 20px;
        }

        @media (max-width: 768px) {
            .container {
                width: 90%;
                max-width: 90%;
            }

            .input-group-buttons {
                flex-direction: column;
            }

            .input-group-buttons button {
                width: 100%;
                margin-bottom: 10px;
            }

            .verify-next button {
                width: 100%;
            }
        }

        @media (max-width: 480px) {
            .top-bar {
                font-size: 20px;
                padding: 10px;
            }

            .input-group input {
                width: calc(100% - 8px);
            }

            .input-group label {
                font-size: 14px;
            }

            .input-group-buttons button {
                font-size: 14px;
                padding: 8px;
            }

            .verify-next button {
                font-size: 14px;
                padding: 8px;
            }
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="top-bar">London Cafe Access</div>
        <div class="content">
            <div class="input-group">
                <label for="employeeId">Employee ID</label>
                <input type="text" id="employeeId" placeholder="Enter Employee ID">
            </div>
            <div class="input-group input-group-buttons">
                <button onclick="enterAsHost()">Enter as Host</button>
                <button onclick="enterAsGuest()">Enter as Guest</button>
            </div>
            <div id="message" class="message"></div>
            <div id="employeeDetails" class="input-group" style="display: none;">
                <label for="employeeName">Employee Name</label>
                <input type="text" id="employeeName" readonly>
            </div>
            <div id="employeeDepartment" class="input-group" style="display: none;">
                <label for="employeeDept">Department</label>
                <input type="text" id="employeeDept" readonly>
            </div>
            <div id="employeePosition" class="input-group" style="display: none;">
                <label for="employeePos">Position</label>
                <input type="text" id="employeePos" readonly>
            </div>
            <div class="spacer"></div>
            <div class="verify-next" id="verifyNextDiv">
                <button onclick="resetForm()">Verify Next Person</button>
            </div>
        </div>
    </div>

    <script>
        function enterAsGuest() {
            const employeeId = document.getElementById('employeeId').value;
            const messageDiv = document.getElementById('message');
            const employeeDetailsDiv = document.getElementById('employeeDetails');
            const employeeDepartmentDiv = document.getElementById('employeeDepartment');
            const employeePositionDiv = document.getElementById('employeePosition');
            const employeeNameInput = document.getElementById('employeeName');
            const employeeDeptInput = document.getElementById('employeeDept');
            const employeePosInput = document.getElementById('employeePos');

            // Clear previous messages and details
            messageDiv.style.display = 'none';
            employeeDetailsDiv.style.display = 'none';
            employeeDepartmentDiv.style.display = 'none';
            employeePositionDiv.style.display = 'none';
            messageDiv.classList.remove('success', 'error');

            if (employeeId.trim() === "") {
                messageDiv.textContent = 'Please enter a valid Employee ID';
                messageDiv.classList.add('error');
                messageDiv.style.display = 'block';
                return;
            }

            // Simulate a database check (replace with actual API call)
            const employees = [
                { id: '123', name: 'John Doe', department: 'Sales', position: 'Manager', hasAccess: true },
                { id: '456', name: 'Jane Smith', department: 'Marketing', position: 'Executive', hasAccess: false },
                { id: '789', name: 'Guest User', department: 'HR', position: 'Assistant', hasAccess: true }
            ];

            const employee = employees.find(emp => emp.id === employeeId);

            if (!employee) {
                messageDiv.textContent = 'Invalid Employee ID';
                messageDiv.classList.add('error');
                messageDiv.style.display = 'block';
                return;
            }

            employeeNameInput.value = employee.name;
            employeeDeptInput.value = employee.department;
            employeePosInput.value = employee.position;
            employeeDetailsDiv.style.display = 'block';
            employeeDepartmentDiv.style.display = 'block';
            employeePositionDiv.style.display = 'block';
            messageDiv.textContent = 'Cafeteria access has been granted';
            messageDiv.classList.add('success');
            messageDiv.style.display = 'block';

            showVerifyNextButton();
        }

        function enterAsHost() {
            const employeeId = document.getElementById('employeeId').value;
            const messageDiv = document.getElementById('message');
            const employeeDetailsDiv = document.getElementById('employeeDetails');
            const employeeDepartmentDiv = document.getElementById('employeeDepartment');
            const employeePositionDiv = document.getElementById('employeePosition');
            const employeeNameInput = document.getElementById('employeeName');
            const employeeDeptInput = document.getElementById('employeeDept');
            const employeePosInput = document.getElementById('employeePos');

            // Clear previous messages and details
            messageDiv.style.display = 'none';
            employeeDetailsDiv.style.display = 'none';
            employeeDepartmentDiv.style.display = 'none';
            employeePositionDiv.style.display = 'none';
            messageDiv.classList.remove('success', 'error');

            if (employeeId.trim() === "") {
                messageDiv.textContent = 'Please enter a valid Employee ID';
                messageDiv.classList.add('error');
                messageDiv.style.display = 'block';
                return;
            }

            // Simulate a database check (replace with actual API call)
            const employees = [
                { id: '123', name: 'John Doe', department: 'Sales', position: 'Manager', hasAccess: true },
                { id: '456', name: 'Jane Smith', department: 'Marketing', position: 'Executive', hasAccess: false }
            ];

            const employee = employees.find(emp => emp.id === employeeId);

            if (!employee) {
                messageDiv.textContent = 'Employee not found';
                messageDiv.classList.add('error');
                messageDiv.style.display = 'block';
            } else if (!employee.hasAccess) {
                messageDiv.textContent = 'Access Denied';
                messageDiv.classList.add('error');
                messageDiv.style.display = 'block';
            } else {
                employeeNameInput.value = employee.name;
                employeeDeptInput.value = employee.department;
                employeePosInput.value = employee.position;
                employeeDetailsDiv.style.display = 'block';
                employeeDepartmentDiv.style.display = 'block';
                employeePositionDiv.style.display = 'block';
                messageDiv.textContent = 'Access Granted';
                messageDiv.classList.add('success');
                messageDiv.style.display = 'block';
            }

            showVerifyNextButton();
        }

        function showVerifyNextButton() {
            const verifyNextDiv = document.getElementById('verifyNextDiv');
            verifyNextDiv.style.display = 'block';
        }

        function resetForm() {
            document.getElementById('employeeId').value = '';
            document.getElementById('employeeName').value = '';
            document.getElementById('employeeDept').value = '';
            document.getElementById('employeePos').value = '';
            document.getElementById('message').style.display = 'none';
            document.getElementById('employeeDetails').style.display = 'none';
            document.getElementById('employeeDepartment').style.display = 'none';
            document.getElementById('employeePosition').style.display = 'none';
            document.getElementById('verifyNextDiv').style.display = 'none';
        }
    </script>
</body>
</html>



import React, { useState, useEffect } from 'react';
import { BrowserRouter as Router, Switch } from 'react-router-dom';
import ProtectedRoute from './ProtectedRoute';
import UpdateCity from './UpdateCity';
import NewCountryForm from './NewCountryForm';
import EditCountry from './EditCountry';
import AddCity from './AddCity';

const App = () => {
  const [isLoading, setIsLoading] = useState(true);
  const [isSuperUser, setIsSuperUser] = useState(false);
  const [isCountryAdmin, setIsCountryAdmin] = useState(false);

  useEffect(() => {
    // Simulate an async operation to fetch user roles
    setTimeout(() => {
      // Set user roles here
      // setIsSuperUser(true/false);
      // setIsCountryAdmin(true/false);

      setIsLoading(false); // After fetching roles
    }, 1000);
  }, []);

  return (
    <Router>
      <Switch>
        {/* Routes for super user */}
        <ProtectedRoute
          path="/admin/editCountry"
          component={EditCountry}
          isLoading={isLoading}
          isAuthorized={isSuperUser}
        />
        <ProtectedRoute
          path="/admin/addCountry"
          component={NewCountryForm}
          isLoading={isLoading}
          isAuthorized={isSuperUser}
        />

        {/* Routes for country admin or super user */}
        <ProtectedRoute
          path="/admin/editCity"
          component={UpdateCity}
          isLoading={isLoading}
          isAuthorized={isSuperUser || isCountryAdmin}
        />

        {/* Route for adding city accessible by both super user and country admin */}
        <ProtectedRoute
          path="/admin/addCity"
          component={AddCity}
          isLoading={isLoading}
          isAuthorized={isSuperUser || isCountryAdmin}
        />

        {/* Fallback for unauthorized access */}
        <ProtectedRoute
          path="*"
          component={AdminAuthError}
          isLoading={isLoading}
          isAuthorized={false}
        />
      </Switch>
    </Router>
  );
};

export default App;
import React from 'react';
import { Route, Redirect } from 'react-router-dom';
import Loader from './Loader';
import AdminAuthError from './AdminAuthError';

const ProtectedRoute = ({ component: Component, isLoading, isAuthorized, ...rest }) => {
  return (
    <Route
      {...rest}
      render={props =>
        isLoading ? (
          <Loader />
        ) : isAuthorized ? (
          <Component {...props} />
        ) : (
          <AdminAuthError />
        )
      }
    />
  );
};

export default ProtectedRoute;

import React, { useEffect, useState } from 'react';
import { useNavigate } from 'react-router-dom';
import axios from 'axios';
import { useNotification } from './NotificationContext';

const FileChecker = () => {
  const [fileAvailable, setFileAvailable] = useState(false);
  const navigate = useNavigate();
  const { notify } = useNotification();

  useEffect(() => {
    const checkFileAvailability = async () => {
      try {
        const response = await axios.get('/api/check-file');
        if (response.data.available) {
          setFileAvailable(true);
        }
      } catch (error) {
        console.error("Error checking file availability", error);
      }
    };

    const interval = setInterval(checkFileAvailability, 60000); // Check every minute

    // Cleanup interval on component unmount
    return () => clearInterval(interval);
  }, []);

  useEffect(() => {
    if (fileAvailable) {
      // Notify the user when the file becomes available
      notify("Your file is now available for download!");
    }
  }, [fileAvailable, notify]);

  return (
    <div>
      {fileAvailable ? (
        <a href="/api/download-file" download>Download File</a>
      ) : (
        <p>File is not yet available. Checking every minute...</p>
      )}
      <button onClick={() => navigate('/some-other-page')}>Go to another page</button>
    </div>
  );
};

export default FileChecker;



import React from 'react';
import ReactDOM from 'react-dom';
import App from './App';
import { NotificationProvider } from './NotificationContext';

ReactDOM.render(
  <NotificationProvider>
    <App />
  </NotificationProvider>,
  document.getElementById('root')
);


import React, { createContext, useContext, useState } from 'react';

const NotificationContext = createContext();

export const useNotification = () => {
  return useContext(NotificationContext);
};

export const NotificationProvider = ({ children }) => {
  const [notification, setNotification] = useState(null);

  const notify = (message) => {
    setNotification(message);
  };

  return (
    <NotificationContext.Provider value={{ notification, notify }}>
      {children}
      {notification && <div className="notification">{notification}</div>}
    </NotificationContext.Provider>
  );
};


import React, { useEffect, useState } from 'react';
import { useNavigate } from 'react-router-dom';
import axios from 'axios';

const FileChecker = () => {
  const [fileAvailable, setFileAvailable] = useState(false);
  const navigate = useNavigate();

  useEffect(() => {
    const checkFileAvailability = async () => {
      try {
        const response = await axios.get('/api/check-file');
        if (response.data.available) {
          setFileAvailable(true);
        }
      } catch (error) {
        console.error("Error checking file availability", error);
      }
    };

    const interval = setInterval(checkFileAvailability, 60000); // Check every minute

    // Cleanup interval on component unmount
    return () => clearInterval(interval);
  }, []);

  useEffect(() => {
    if (fileAvailable) {
      // Notify the user when the file becomes available
      alert("Your file is now available for download!");
    }
  }, [fileAvailable]);

  return (
    <div>
      {fileAvailable ? (
        <a href="/api/download-file" download>Download File</a>
      ) : (
        <p>File is not yet available. Checking every minute...</p>
      )}
      <button onClick={() => navigate('/some-other-page')}>Go to another page</button>
    </div>
  );
};

export default FileChecker;



import React, { useState, useEffect } from 'react';

const FileChecker = () => {
  const [file1Available, setFile1Available] = useState(null);
  const [file2Available, setFile2Available] = useState(null);
  const [timer, setTimer] = useState(300); // 5 minutes in seconds
  const [retryAllowed, setRetryAllowed] = useState(false);

  useEffect(() => {
    const checkFiles = async () => {
      try {
        // Simulating API calls
        const response1 = await fetch('/api/checkFile1');
        const response2 = await fetch('/api/checkFile2');
        setFile1Available(response1.ok);
        setFile2Available(response2.ok);
        if (!response1.ok || !response2.ok) {
          setRetryAllowed(false);
          setTimer(300);
        }
      } catch (error) {
        console.error('Error checking files:', error);
      }
    };

    checkFiles();
  }, []); // Run on component mount

  useEffect(() => {
    let timerInterval;
    if (!retryAllowed && (file1Available === false || file2Available === false)) {
      timerInterval = setInterval(() => {
        setTimer((prev) => {
          if (prev > 0) return prev - 1;
          clearInterval(timerInterval);
          setRetryAllowed(true);
          return 0;
        });
      }, 1000);
    }
    return () => clearInterval(timerInterval);
  }, [file1Available, file2Available, retryAllowed]);

  const retryCheck = () => {
    setRetryAllowed(false);
    setFile1Available(null);
    setFile2Available(null);
    setTimer(300);
    // Trigger API checks again
    checkFiles();
  };

  return (
    <div>
      <h1>File Checker</h1>
      {file1Available !== null && (
        <div>
          {file1Available ? (
            <a href="/api/downloadFile1">Download File 1</a>
          ) : (
            <p>File 1 not available. Retrying in {timer} seconds...</p>
          )}
        </div>
      )}
      {file2Available !== null && (
        <div>
          {file2Available ? (
            <a href="/api/downloadFile2">Download File 2</a>
          ) : (
            <p>File 2 not available. Retrying in {timer} seconds...</p>
          )}
        </div>
      )}
      {retryAllowed && <button onClick={retryCheck}>Retry Now</button>}
    </div>
  );
};

export default FileChecker;


import React, { useState } from 'react';
import styled from 'styled-components';
import ProgressBar from './ProgressBar';

const App = () => {
  const [step, setStep] = useState(1);
  const [fileType, setFileType] = useState('');
  const [file, setFile] = useState(null);

  const handleNext = () => {
    setStep(prev => prev + 1);
  };

  const handlePrevious = () => {
    setStep(prev => prev - 1);
  };

  const handleFileTypeChange = (event) => {
    setFileType(event.target.value);
  };

  const handleFileChange = (event) => {
    setFile(event.target.files[0]);
  };

  const handleUpload = () => {
    // Logic to upload file
    handleNext();
  };

  const triggerAnalysis = () => {
    // Logic to trigger analysis
    handleNext();
  };

  return (
    <Container>
      <ProgressBar step={step} />
      {step === 1 && (
        <Step>
          <h2>Select File Type</h2>
          <select onChange={handleFileTypeChange} value={fileType}>
            <option value="" disabled>Select file type</option>
            <option value="image">Image</option>
            <option value="document">Document</option>
            <option value="video">Video</option>
          </select>
          <Button onClick={handleNext} disabled={!fileType}>Next</Button>
        </Step>
      )}
      {step === 2 && (
        <Step>
          <h2>Upload File</h2>
          <input type="file" onChange={handleFileChange} />
          <Button onClick={handlePrevious}>Previous</Button>
          <Button onClick={handleUpload} disabled={!file}>Upload</Button>
        </Step>
      )}
      {step === 3 && (
        <Step>
          <h2>Trigger Analysis</h2>
          <Button onClick={handlePrevious}>Previous</Button>
          <Button onClick={triggerAnalysis}>Analyze</Button>
        </Step>
      )}
      {step === 4 && (
        <Step>
          <h2>Analysis Complete</h2>
        </Step>
      )}
    </Container>
  );
};

export default App;

const Container = styled.div`
  max-width: 600px;
  margin: 0 auto;
  padding: 20px;
  text-align: center;
`;

const Step = styled.div`
  margin-top: 20px;
`;

const Button = styled.button`
  margin: 10px;
  padding: 10px 20px;
  background-color: #007BFF;
  color: white;
  border: none;
  cursor: pointer;

  &:disabled {
    background-color: #CCC;
    cursor: not-allowed;
  }
`;




import React from 'react';
import styled from 'styled-components';

const ProgressBar = ({ step }) => {
  return (
    <ProgressContainer>
      <ProgressStep active={step >= 1}>Select File Type</ProgressStep>
      <ProgressStep active={step >= 2}>Upload File</ProgressStep>
      <ProgressStep active={step >= 3}>Trigger Analysis</ProgressStep>
    </ProgressContainer>
  );
};

export default ProgressBar;

const ProgressContainer = styled.div`
  display: flex;
  justify-content: space-between;
  margin-bottom: 20px;
`;

const ProgressStep = styled.div`
  flex: 1;
  text-align: center;
  padding: 10px;
  background-color: $we{props => (props.active ? '#007BFF' : '#CCC')};
  color: white;
  border: 1px solid #007BFF;

  &:not(:last-child) {
    margin-right: 10px;
  }
`;



import React, { useState, useRef, useContext, useCallback } from 'react';
import { useHistory } from 'react-router-dom';
import { AdminCountryListContext } from './context';
import { toast } from 'react-toastify';

export default function UpdateCity() {
  const history = useHistory();
  const cityGridRef = useRef();
  const [data, setData] = useState([]);
  const temp = useContext(AdminCountryListContext);
  const userCountryList = temp.adminCountryList;

  const [cityId, setCityId] = useState('');
  const [displayName, setDisplayName] = useState('');
  const [urlParamName, setURLParamName] = useState('');
  const [active, setActive] = useState('');
  const [countryID, setCountryID] = useState('');
  const [countrySearchList, setCountrySearchList] = useState([]);
  const [selectedCountry, setSelectedCountry] = useState('');
  const [updatedRecord, setUpdatedRecord] = useState(false);
  const [oldName, setOldName] = useState('');
  const [oldParam, setOldParam] = useState('');
  const [urlParamNameError, setUrlParamNameError] = useState('');
  const [displayNameError, setDisplayNameError] = useState('');

  const refreshGrid = useCallback(() => {
    if (cityGridRef.current?.api !== undefined) {
      const params = { force: true };
      cityGridRef.current.api.refreshCells(params);
    }
  }, [cityGridRef]);

  const saveCity = async (cityId, displayName, urlParamName, countryId, isActive) => {
    // Implement the saveCity logic here
  };

  const useCheckboxColumnRenderer = (params) => {
    const [isChecked, setIsChecked] = useState(params.data.active);

    const onChangeCheckBoxHandler = async (event) => {
      await saveCity(params.data.cityId, params.data.displayName, params.data.urlParamName, params.data.countryId, isChecked);
      toast.success(`${params.data.displayName} has been ${params.data.active ? 'Disabled' : 'Enabled'}`);
      setIsChecked(!isChecked);
      refreshGrid();
    };

    return (
      <label className="switch">
        <input type="checkbox" defaultChecked={isChecked} onChange={onChangeCheckBoxHandler} />
        <span className="slider round"></span>
      </label>
    );
  };

  const actionsColumnRender = (params) => {
    const editingCells = params.api.getEditingCells();
    const isCurrentRowEditing = editingCells.some(cell => cell.rowIndex === params.node.rowIndex);

    if (isCurrentRowEditing) {
      return (
        <div className="actions_buttons_div">
          <div className="edit_button_div">
            <button className="btn pushable btn-success save_buttonCustom" data-action="update">Save</button>
          </div>
          <div className="disable_button_div">
            <button className="btn pushable btn-dark cancel_custom" data-action="cancel">Cancel</button>
          </div>
        </div>
      );
    }
  };

  const onRowEditingStarted = (params) => {
    params.api.refreshCells({
      columns: ['action'],
      rowNodes: [params.node],
      force: true
    });
  };

  const onRowEditingStopped = (params) => {
    const currentRow = params.node.data;
    const name = currentRow.displayName.trim();
    const urlName = currentRow.urlParamName.trim();

    let valid = true;

    if (name === '') {
      setDisplayNameError("City display name cannot be empty");
      valid = false;
    } else if (data.some(city => city.displayName.toLowerCase() === name.toLowerCase() && city.cityId !== currentRow.cityId)) {
      setDisplayNameError("Duplicate city name");
      valid = false;
    } else {
      setDisplayNameError("");
    }

    if (urlName === '') {
      setUrlParamNameError("Url Param name cannot be empty");
      valid = false;
    } else if (data.some(city => city.urlParamName.toLowerCase() === urlName.toLowerCase() && city.cityId !== currentRow.cityId)) {
      setUrlParamNameError("City with Url Param name in the selected country already exists");
      valid = false;
    } else {
      setUrlParamNameError("");
    }

    if (!valid) {
      toast.error(`Oops! Resolve the displayed errors: ${displayNameError} ${urlParamNameError}`, {
        closeOnClick: true,
        autoClose: 7000,
      });
      params.api.startEditingCell({
        rowIndex: params.node.rowIndex,
        colKey: params.columnApi.getAllDisplayedColumns()[0].colId
      });
    } else {
      saveCity(currentRow.cityId, currentRow.displayName, currentRow.urlParamName, selectedCountry.countryID, currentRow.active)
        .then(() => {
          toast.success(`${currentRow.displayName} has been updated`);
        })
        .catch(error => {
          toast.error(`Error updating ${currentRow.displayName}: ${error.message}`);
        });
      setUpdatedRecord(false);
    }
    refreshGrid();
  };

  const handleDisplayName = async (name) => {
    setDisplayName(name);
    if (name.trim() === '') {
      setDisplayNameError("City display name cannot be empty");
    } else if (data.some(city => city.displayName.toLowerCase() === name.trim().toLowerCase())) {
      setDisplayNameError("Duplicate city name");
    } else {
      setDisplayNameError("");
    }
  };

  const handleUrlParamName = async (name) => {
    setURLParamName(name);
    if (name.trim() === '') {
      setUrlParamNameError("Url Param name cannot be empty");
    } else if (data.some(city => city.urlParamName.toLowerCase() === name.trim().toLowerCase())) {
      setUrlParamNameError("City with Url Param name in the selected country already exists");
    } else {
      setUrlParamNameError("");
    }
  };

  const onCellClicked = (params) => {
    if (params.column.colId === 'action' && params.event.target.dataset.action) {
      const action = params.event.target.dataset.action;
      if (action === "edit") {
        if (updatedRecord) {
          toast.error("Only one record can be updated at a time! Please save the changes before editing another record.");
        }
      } else if (action === "update") {
        params.api.stopEditing({ cancel: false });
        const currentRow = params.node.data;
        const name = currentRow.displayName;
        const urlName = currentRow.urlParamName;

        handleDisplayName(name);
        handleUrlParamName(urlName);
      }
    }
  };

  return (
    <div>
      {/* Render grid or other components here */}
    </div>
  );
}
