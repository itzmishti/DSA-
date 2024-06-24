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
      params.api.startEditingCell({ rowIndex: params.node.rowIndex, colKey: 'displayName' });
    } else {
      params.api.refreshCells({
        columns: ['action'],
        rowNodes: [params.node],
        force: true
      });
    }
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
