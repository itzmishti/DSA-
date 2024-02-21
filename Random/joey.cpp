import React, { useState } from 'react';
import axios from 'axios';
import { CSVLink } from 'react-csv';

function App() {
  const [jsonData, setJsonData] = useState(null);

  // Function to fetch data from API
  const fetchData = async () => {
    try {
      const response = await axios.get('YOUR_API_ENDPOINT');
      setJsonData(response.data);
    } catch (error) {
      console.error('Error fetching data:', error);
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
      <button onClick={fetchData}>Fetch Data</button>
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

export default App;
