import React, { useState } from 'react';
import DatePicker from 'react-datepicker';
import 'react-datepicker/dist/react-datepicker.css';

const MyModal = ({ showModal, closeModal, onSelectDates }) => {
  const [startDate, setStartDate] = useState(null);
  const [endDate, setEndDate] = useState(null);

  const handleConfirm = () => {
    if (startDate && endDate) {
      onSelectDates(startDate, endDate);
      closeModal();
    } else {
      alert('Please select both start and end dates.');
    }
  };

  return (
    <div className={`modal ${showModal ? 'show' : 'hide'}`}>
      <div className="modal-content">
        <span className="close" onClick={closeModal}>&times;</span>
        <h2>Select Dates</h2>
        <div className="date-picker">
          <DatePicker
            selected={startDate}
            onChange={(date) => setStartDate(date)}
            selectsStart
            startDate={startDate}
            endDate={endDate}
            placeholderText="Start Date"
          />
          <DatePicker
            selected={endDate}
            onChange={(date) => setEndDate(date)}
            selectsEnd
            startDate={startDate}
            endDate={endDate}
            minDate={startDate}
            placeholderText="End Date"
          />
        </div>
        <button onClick={handleConfirm}>Confirm</button>
      </div>
    </div>
  );
};

const MyComponent = () => {
  const [showModal, setShowModal] = useState(false);

  const openModal = () => {
    setShowModal(true);
  };

  const closeModal = () => {
    setShowModal(false);
  };

  const handleSelectDates = (startDate, endDate) => {
    // Call your function with selected dates
    console.log('Selected dates:', startDate, endDate);
    // Replace this with your actual function call
  };

  return (
    <div>
      <button onClick={openModal}>Open Modal</button>
      <MyModal
        showModal={showModal}
        closeModal={closeModal}
        onSelectDates={handleSelectDates}
      />
    </div>
  );
};

export default MyComponent;
