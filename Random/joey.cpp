import React, { useState } from 'react';
import { CSVLink } from 'react-csv';

function App() {
  const [jsonData, setJsonData] = useState(null);
  const [argument1, setArgument1] = useState('initialValue');
  const [argument2, setArgument2] = useState('initialValue');

  // Function to call your API and retrieve data
  const callYourApiFunction = async (arg1, arg2) => {
    try {
      // Call your API function here with arguments
      const response = await yourApiFunction(arg1, arg2);
      setJsonData(response);
    } catch (error) {
      console.error('Error calling your API:', error);
    }
  };

  // Function to convert JSON to CSV
  const convertToCSV = () => {
    if (!jsonData) return;

    const csvData = [];
    const headers = Object.keys(jsonData[0]);
    csvData.push(headers.join(','));

    jsonData.forEach((item) => {
      const values = headers.map((header) => item[header]);
      csvData.push(values.join(','));
    });

    return csvData.join('\n');
  };

  return (
    <div>
      <button onClick={() => callYourApiFunction(argument1, argument2)}>Fetch Data</button>
      {jsonData && (
        <div>
          <h2>Data:</h2>
          <pre>{JSON.stringify(jsonData, null, 2)}</pre>
          <CSVLink
            data={convertToCSV()}
            filename={'data.csv'}
            className="btn btn-primary"
            target="_blank"
          >
            Download CSV
          </CSVLink>
        </div>
      )}
    </div>
  );
}

// Replace this with your actual API function
const yourApiFunction = async (arg1, arg2) => {
  // Example of fetching data from an API with arguments
  const response = await fetch(`YOUR_API_ENDPOINT?arg1=${arg1}&arg2=${arg2}`);
  if (!response.ok) {
    throw new Error('Failed to fetch data from the API');
  }
  const data = await response.json();
  return data;
};

export default App;
