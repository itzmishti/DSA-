import React, { useState } from 'react';
import './Modal.css'; // Import your CSS file for styling

const Modal = ({ isOpen, onClose, children }) => {
  if (!isOpen) return null;

  const handleClose = () => {
    onClose();
  };

  return (
    <div className="modal-overlay" onClick={onClose}>
      <div className="modal-content" onClick={(e) => e.stopPropagation()}>
        <button className="modal-close" onClick={handleClose}>X</button>
        {children}
        <button onClick={handleClose}>Close Modal</button>
      </div>
    </div>
  );
};

const App = () => {
  const [isOpen, setIsOpen] = useState(false);

  const openModal = () => {
    setIsOpen(true);
  };

  const closeModal = () => {
    setIsOpen(false);
  };

  return (
    <div className="App">
      <button onClick={openModal}>Open Modal</button>
      <Modal isOpen={isOpen} onClose={closeModal}>
        <h2>This is a Modal</h2>
        <p>You can put any content here.</p>
      </Modal>
    </div>
  );
};

export default App;















import React, { useState } from 'react';
import './Modal.css'; // Import your CSS file for styling

const Modal = ({ isOpen, onClose, children }) => (
  isOpen ? (
    <div className="modal-overlay" onClick={onClose}>
      <div className="modal-content" onClick={(e) => e.stopPropagation()}>
        <button className="modal-close" onClick={onClose}>X</button>
        {children}
        <button onClick={onClose}>Close Modal</button>
      </div>
    </div>
  ) : null
);

const App = () => {
  const [isOpen, setIsOpen] = useState(false);

  return (
    <div className="App">
      <button onClick={() => setIsOpen(true)}>Open Modal</button>
      <Modal isOpen={isOpen} onClose={() => setIsOpen(false)}>
        <h2>This is a Modal</h2>
        <p>You can put any content here.</p>
      </Modal>
    </div>
  );
};

export default App;

