import React, { createContext, useState, useEffect } from 'react';

// Create the context
export const RolesContext = createContext();

// Create a provider component
export const RolesProvider = ({ children }) => {
  const [roles, setRoles] = useState([]);

  useEffect(() => {
    // Check if roles are already in local storage
    const storedRoles = localStorage.getItem('roles');
    if (storedRoles) {
      setRoles(JSON.parse(storedRoles));
    } else {
      // If not, fetch the roles from the API
      fetchRoles();
    }
  }, []);

  const fetchRoles = async () => {
    try {
      const response = await fetch('/api/roles'); // Replace with your API endpoint
      const roles = await response.json();
      setRoles(roles);
      localStorage.setItem('roles', JSON.stringify(roles));
    } catch (error) {
      console.error('Failed to fetch roles:', error);
    }
  };

  return (
    <RolesContext.Provider value={roles}>
      {children}
    </RolesContext.Provider>
  );
};




import React from 'react';
import { RolesProvider } from './RolesContext';
import YourMainComponent from './YourMainComponent';

const App = () => {
  return (
    <RolesProvider>
      <YourMainComponent />
    </RolesProvider>
  );
};

export default App;




import React, { useContext } from 'react';
import { RolesContext } from './RolesContext';

const SomePage = () => {
  const roles = useContext(RolesContext);

  return (
    <div>
      <h1>Roles</h1>
      <ul>
        {roles.map(role => (
          <li key={role.id}>{role.name}</li>
        ))}
      </ul>
    </div>
  );
};

export default SomePage;


export const RolesProvider = ({ children }) => {
  const [roles, setRoles] = useState([]);

  useEffect(() => {
    const storedRoles = localStorage.getItem('roles');
    if (storedRoles) {
      setRoles(JSON.parse(storedRoles));
    } else {
      fetchRoles();
    }
  }, []);

  const fetchRoles = async () => {
    try {
      const response = await fetch('/api/roles'); 
      const roles = await response.json();
      setRoles(roles);
      localStorage.setItem('roles', JSON.stringify(roles));
    } catch (error) {
      console.error('Failed to fetch roles:', error);
    }
  };

  const clearRoles = () => {
    setRoles([]);
    localStorage.removeItem('roles');
  };

  return (
    <RolesContext.Provider value={{ roles, fetchRoles, clearRoles }}>
      {children}
    </RolesContext.Provider>
  );
};








import React, { createContext, useState, useEffect } from 'react';

// Create the context
export const RolesContext = createContext();

// Create a provider component
export const RolesProvider = ({ children }) => {
  const [roles, setRoles] = useState([]);

  useEffect(() => {
    const storedRoles = localStorage.getItem('roles');
    if (storedRoles) {
      setRoles(JSON.parse(storedRoles));
    } else {
      fetchRoles();
    }
  }, []);

  const fetchRoles = async () => {
    try {
      const response = await fetch('/api/roles'); // Replace with your API endpoint
      const roles = await response.json();
      setRoles(roles);
      localStorage.setItem('roles', JSON.stringify(roles));
    } catch (error) {
      console.error('Failed to fetch roles:', error);
    }
  };

  const clearRoles = () => {
    setRoles([]);
    localStorage.removeItem('roles');
  };

  return (
    <RolesContext.Provider value={{ roles, fetchRoles, clearRoles }}>
      {children}
    </RolesContext.Provider>
  );
};


import React from 'react';
import { RolesProvider } from './RolesContext';
import MainPage from './MainPage';
import SomePage from './SomePage';
import { BrowserRouter as Router, Route, Switch } from 'react-router-dom';

const App = () => {
  return (
    <RolesProvider>
      <Router>
        <Switch>
          <Route path="/" exact component={MainPage} />
          <Route path="/somepage" component={SomePage} />
        </Switch>
      </Router>
    </RolesProvider>
  );
};

export default App;


import React from 'react';

const MainPage = () => {
  return (
    <div>
      <h1>Main Page</h1>
      <p>Welcome to the main page!</p>
    </div>
  );
};

export default MainPage;


import React, { useContext, useEffect } from 'react';
import { RolesContext } from './RolesContext';

const SomePage = () => {
  const { roles, fetchRoles } = useContext(RolesContext);

  useEffect(() => {
    if (roles.length === 0) {
      fetchRoles();
    }
  }, [roles, fetchRoles]);

  return (
    <div>
      <h1>Roles</h1>
      <ul>
        {roles.map(role => (
          <li key={role.id}>{role.name}</li>
        ))}
      </ul>
    </div>
  );
};

export default SomePage;
