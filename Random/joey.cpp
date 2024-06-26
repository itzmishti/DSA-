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
