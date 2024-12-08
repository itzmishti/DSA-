<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Guest Analysis Dashboard</title>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/xlsx/0.18.5/xlsx.full.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/highcharts/11.3.0/highcharts.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/highcharts/11.3.0/modules/sunburst.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/highcharts/11.3.0/modules/treemap.js"></script>
    <style>
        body {
            font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
            margin: 0;
            padding: 20px;
            background-color: #f8f9fa;
        }
        .container {
            max-width: 1400px;
            margin: 0 auto;
            background-color: white;
            padding: 30px;
            border-radius: 12px;
            box-shadow: 0 4px 6px rgba(0,0,0,0.1);
        }
        .upload-section {
            text-align: center;
            padding: 40px;
            border: 2px dashed #e0e0e0;
            border-radius: 12px;
            margin-bottom: 30px;
            background-color: #fafafa;
        }
        .dashboard {
            display: none;
        }
        .date-range {
            margin: 20px 0;
            padding: 20px;
            background-color: #f8f9fa;
            border-radius: 8px;
            border: 1px solid #e9ecef;
        }
        .charts-container {
            display: grid;
            grid-template-columns: 1fr 1fr;
            gap: 20px;
            margin-top: 20px;
        }
        .chart {
            min-height: 400px;
            background-color: white;
            border-radius: 8px;
            padding: 15px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
        }
        .full-width {
            grid-column: 1 / -1;
            min-height: 600px;
        }
        .stats-container {
            display: grid;
            grid-template-columns: repeat(5, 1fr);
            gap: 15px;
            margin-bottom: 20px;
        }
        .stat-card {
            background: white;
            padding: 20px;
            border-radius: 8px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.1);
            text-align: center;
        }
        .stat-value {
            font-size: 24px;
            font-weight: bold;
            color: #0d6efd;
        }
        .stat-label {
            color: #6c757d;
            margin-top: 5px;
        }
    </style>
</head>
<body>
    <div class="container">
        <div id="uploadSection" class="upload-section">
            <h2>Partner's Dining Dashboard</h2>
            <p>Upload your Excel file to begin the analysis</p>
            <input type="file" id="fileInput" accept=".xlsx,.xls" />
        </div>

        <div id="dashboard" class="dashboard">
            <div class="date-range">
                <input type="date" id="startDate" />
                <input type="date" id="endDate" />
                <button onclick="updateDashboard()">Apply Filter</button>
                <button onclick="resetDateFilter()">Reset</button>
            </div>

            <div class="stats-container" id="statsContainer"></div>
            
            <div class="charts-container">
                <div id="sunburstChart" class="chart full-width"></div>
                <div id="lobDistribution" class="chart"></div>
                <div id="guestTrends" class="chart"></div>
            </div>
        </div>
    </div>

<script>
let globalData = [];

document.getElementById('fileInput').addEventListener('change', function(e) {
    const file = e.target.files[0];
    const reader = new FileReader();
    
    reader.onload = function(e) {
        const data = new Uint8Array(e.target.result);
        const workbook = XLSX.read(data, {type: 'array'});
        const firstSheet = workbook.Sheets[workbook.SheetNames[0]];
        globalData = XLSX.utils.sheet_to_json(firstSheet);
        
        document.getElementById('uploadSection').style.display = 'none';
        document.getElementById('dashboard').style.display = 'block';
        
        initializeDashboard();
    };
    
    reader.readAsArrayBuffer(file);
});
function updateStats(filteredData, selectedCostCenter = null) {
    let dataToUse = filteredData;
    
    // Filter data if a cost center is selected
    if (selectedCostCenter) {
        dataToUse = filteredData.filter(row => row.CostCenter === selectedCostCenter);
    }

    const stats = {
        totalHosts: new Set(dataToUse.map(row => row.SID)).size,
        totalGuests: dataToUse.reduce((sum, row) => sum + (parseInt(row.GuestCount) || 0), 0),
        uniqueGuests: new Set(
            dataToUse
                .filter(row => row['GuestsSID(s)'])
                .flatMap(row => row['GuestsSID(s)'].split(',').map(sid => sid.trim()))
                .filter(sid => sid)
        ).size,
        uniqueHosts: new Set(
            dataToUse
                .filter(row => row['SID'])
                .flatMap(row => row['SID'].split(',').map(sid => sid.trim()))
                .filter(sid => sid)
        ).size,
    };

    // Calculate total people (hosts + guests)
    stats.totalPeople = stats.totalHosts + stats.totalGuests;

    // Create a label for the current selection
    let selectionLabel = selectedCostCenter ? ` in ${selectedCostCenter}` : '';

    const statsContainer = document.getElementById('statsContainer');
    statsContainer.innerHTML = `
        <div class="stat-card">
            <div class="stat-value">${stats.totalHosts}</div>
            <div class="stat-label">Total Hosts${selectionLabel}</div>
        </div>
        <div class="stat-card">
            <div class="stat-value">${stats.totalGuests}</div>
            <div class="stat-label">Total Guests${selectionLabel}</div>
        </div>
        <div class="stat-card">
            <div class="stat-value">${stats.totalPeople}</div>
            <div class="stat-label">Total People${selectionLabel}</div>
        </div>
        <div class="stat-card">
            <div class="stat-value">${stats.uniqueHosts}</div>
            <div class="stat-label">Unique Hosts${selectionLabel}</div>
        </div>
        <div class="stat-card">
            <div class="stat-value">${stats.uniqueGuests}</div>
            <div class="stat-label">Unique Guests${selectionLabel}</div>
        </div>
    `;
}

function createSunburstData(filteredData) {
    const data = [{
        id: 'root',
        parent: '',
        name: 'All Cost Centers'
    }];

    // First create a structured map of the data
    const costCenterMap = new Map();

    // Process each row
    filteredData.forEach(row => {
        const costCenter = row.CostCenter;
        const sid = row.SID;
        const guestsSIDs = row['GuestsSID(s)'];
        const entryDate = row.Modified;

        // Skip if no cost center
        if (!costCenter) return;

        // Initialize cost center if not exists
        if (!costCenterMap.has(costCenter)) {
            costCenterMap.set(costCenter, {
                guestCount: 0,
                hosts: new Map()
            });
        }

        const centerData = costCenterMap.get(costCenter);
        
        // Add or update host data if they're bringing guests
        if (sid && row.bringingGuests) {
            if (!centerData.hosts.has(sid)) {
                centerData.hosts.set(sid, {
                    sid: sid,
                    firstName: row.FirstName || '',
                    lastName: row.LastName || '',
                    title: row.TitleCheck || '',
                    entries: [] // Array to store multiple entries
                });
            }
            
            // Add this entry to the host's entries
            centerData.hosts.get(sid).entries.push({
                date: entryDate,
                guests: new Set(guestsSIDs ? guestsSIDs.split(',').map(g => g.trim()).filter(g => g) : []),
                guestCount: parseInt(row.GuestCount) || 0
            });
        }

        // Update total guest count for the cost center
        if (row.bringingGuests) {
            centerData.guestCount += parseInt(row.GuestCount) || 0;
        }
    });

    // Build the sunburst data structure
    costCenterMap.forEach((centerData, costCenter) => {
        // Add cost center node
        data.push({
            id: `cc-${costCenter}`,
            parent: 'root',
            name: `${costCenter} (${centerData.guestCount} guests)`,
            value: Math.max(centerData.guestCount, 1)
        });

        // Add hosts for this cost center
        centerData.hosts.forEach((hostData, sid) => {
            // Add host node with total guests across all entries
            const totalHostGuests = hostData.entries.reduce((sum, entry) => sum + entry.guestCount, 0);
            const hostNodeId = `host-${sid}`;
            
            data.push({
                id: hostNodeId,
                parent: `cc-${costCenter}`,
                name: `${hostData.firstName} ${hostData.lastName} - ${hostData.title} (${totalHostGuests} total)`,
                value: Math.max(totalHostGuests, 1)
            });

            // Add entry nodes for this host
            hostData.entries.forEach((entry, index) => {
                const entryDate = new Date(entry.date).toLocaleDateString();
                const entryNodeId = `entry-${sid}-${index}`;
                
                // Add entry node
                data.push({
                    id: entryNodeId,
                    parent: hostNodeId,
                    name: `Visit on ${entryDate} (${entry.guestCount} guests)`,
                    value: Math.max(entry.guestCount, 1)
                });

                // Add guest nodes for this entry
                entry.guests.forEach(guestSid => {
                    data.push({
                        id: `guest-${guestSid}-${sid}-${index}`,
                        parent: entryNodeId,
                        name: `Guest: ${guestSid}`,
                        value: 1
                    });
                });
            });
        });
    });

    return data;
}

function updateSunburst(filteredData) {
    const chartData = createSunburstData(filteredData);
    
    if (chartData.length <= 1) {
        console.warn('No data available for sunburst chart');
        return;
    }

    Highcharts.chart('sunburstChart', {
        chart: {
            height: '600px'
        },
        title: {
            text: 'Guest Distribution by Cost Center and Host'
        },
        subtitle: {
            text: 'Click to drill down into cost centers, hosts, and visits'
        },
        // Add click events for selection
        plotOptions: {
            series: {
                cursor: 'pointer',
                point: {
                    events: {
                        click: function() {
                            // Get the selected node's data
                            const point = this;
                            const id = point.id;
                            
                            if (id.startsWith('cc-')) {
                                // Cost center selected
                                const costCenter = id.replace('cc-', '').split(' (')[0];
                                updateStats(filteredData, costCenter);
                            } else if (id === 'root') {
                                // Root node selected - show all stats
                                updateStats(filteredData);
                            }
                        }
                    }
                }
            }
        },
        series: [{
            type: 'sunburst',
            data: chartData,
            allowDrillToNode: true,
            cursor: 'pointer',
            dataLabels: {
                format: '{point.name}',
                filter: {
                    property: 'innerArcLength',
                    operator: '>',
                    value: 16
                },
                style: {
                    textOverflow: 'ellipsis'
                }
            },
            levels: [{
                level: 1,
                levelIsConstant: false,
                dataLabels: {
                    rotationMode: 'parallel',
                    filter: {
                        property: 'outerArcLength',
                        operator: '>',
                        value: 64
                    }
                }
            }, {
                level: 2,
                colorByPoint: true,
                dataLabels: {
                    rotationMode: 'parallel'
                }
            }, {
                level: 3,
                colorVariation: {
                    key: 'brightness',
                    to: -0.3
                }
            }, {
                level: 4,
                colorVariation: {
                    key: 'brightness',
                    to: -0.5
                }
            }]
        }]
    });
}


function updateLOBDistribution(filteredData) {
    const lobData = {};
    filteredData.forEach(row => {
        if (!lobData[row.LOB]) lobData[row.LOB] = 0;
        lobData[row.LOB] += parseInt(row.GuestCount) || 0;
    });

    Highcharts.chart('lobDistribution', {
        chart: {
            type: 'pie'
        },
        title: {
            text: 'Guest Distribution by Line of Business'
        },
        series: [{
            name: 'Guests',
            data: Object.entries(lobData).map(([lob, count]) => ({
                name: lob,
                y: count
            }))
        }]
    });
}

function updateGuestTrends(filteredData) {
    // Process data
    const trends = {};
    filteredData.forEach(row => {
        const date = row.Modified.split('T')[0];
        if (!trends[date]) trends[date] = 0;
        trends[date] += parseInt(row.GuestCount) || 0;
    });

    const sortedDates = Object.keys(trends).sort();
    const guestData = sortedDates.map(date => trends[date]);

    // Calculate moving average for trend line
    const movingAveragePeriod = 7;
    const movingAverage = guestData.map((value, index, array) => {
        const start = Math.max(0, index - movingAveragePeriod + 1);
        const end = index + 1;
        const subset = array.slice(start, end);
        return subset.reduce((sum, val) => sum + val, 0) / subset.length;
    });

    Highcharts.chart('guestTrends', {
        chart: {
            type: 'area',
            style: {
                fontFamily: '-apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif'
            },
            backgroundColor: {
                linearGradient: { x1: 0, y1: 0, x2: 0, y2: 1 },
                stops: [
                    [0, '#ffffff'],
                    [1, '#f8f9fa']
                ]
            }
        },
        title: {
            text: 'Guest Count Trends Over Time',
            style: {
                fontSize: '20px',
                fontWeight: 'bold',
                color: '#2c3e50'
            }
        },
        subtitle: {
            text: 'Daily guest counts with 7-day moving average',
            style: {
                color: '#7f8c8d'
            }
        },
        xAxis: {
            categories: sortedDates,
            labels: {
                rotation: -45,
                style: {
                    fontSize: '12px',
                    color: '#34495e'
                }
            },
            tickLength: 5,
            lineColor: '#e0e0e0',
            gridLineWidth: 1,
            gridLineColor: 'rgba(224, 224, 224, 0.5)'
        },
        yAxis: {
            title: {
                text: 'Number of Guests',
                style: {
                    color: '#2c3e50',
                    fontSize: '14px'
                }
            },
            gridLineColor: 'rgba(224, 224, 224, 0.5)',
            labels: {
                style: {
                    color: '#34495e'
                }
            }
        },
        tooltip: {
            shared: true,
            backgroundColor: 'rgba(255, 255, 255, 0.95)',
            borderWidth: 0,
            shadow: true,
            useHTML: true,
            headerFormat: '<div style="font-size: 12px; font-weight: bold; padding: 8px;">{point.key}</div>',
            pointFormat: '<div style="color: {series.color}; padding: 3px;">' +
                '<span style="font-weight: bold;">{series.name}:</span> ' +
                '<span>{point.y:.0f} guests</span></div>'
        },
        plotOptions: {
            area: {
                fillOpacity: 0.3,
                marker: {
                    enabled: false,
                    symbol: 'circle',
                    radius: 4,
                    states: {
                        hover: {
                            enabled: true
                        }
                    }
                },
                states: {
                    hover: {
                        lineWidth: 3
                    }
                }
            },
            series: {
                pointStart: 0,
                animation: {
                    duration: 1500
                }
            }
        },
        series: [{
            name: 'Daily Guest Count',
            data: guestData,
            color: '#3498db',
            fillColor: {
                linearGradient: {
                    x1: 0,
                    y1: 0,
                    x2: 0,
                    y2: 1
                },
                stops: [
                    [0, Highcharts.color('#3498db').setOpacity(0.3).get('rgba')],
                    [1, Highcharts.color('#3498db').setOpacity(0).get('rgba')]
                ]
            }
        }, {
            name: '7-Day Moving Average',
            data: movingAverage,
            type: 'spline',
            color: '#e74c3c',
            lineWidth: 2,
            marker: {
                enabled: false
            },
            states: {
                hover: {
                    lineWidth: 3
                }
            }
        }],
        legend: {
            enabled: true,
            align: 'center',
            verticalAlign: 'bottom',
            itemStyle: {
                color: '#2c3e50',
                fontWeight: 'normal'
            },
            itemHoverStyle: {
                color: '#34495e'
            }
        },
        credits: {
            enabled: false
        },
        responsive: {
            rules: [{
                condition: {
                    maxWidth: 500
                },
                chartOptions: {
                    legend: {
                        layout: 'horizontal',
                        align: 'center',
                        verticalAlign: 'bottom'
                    }
                }
            }]
        }
    });
}

function updateDashboard() {
    const filteredData = filterDataByDateRange();
    updateStats(filteredData); // Initial stats with no cost center selected
    updateSunburst(filteredData);
    updateLOBDistribution(filteredData);
    updateGuestTrends(filteredData);
}

// Add a reset function to the window object so it can be called from HTML
window.resetDashboard = function() {
    const filteredData = filterDataByDateRange();
    updateStats(filteredData); // Reset stats to show all data
    initializeDashboard();
};

function filterDataByDateRange() {
    const startDate = new Date(document.getElementById('startDate').value);
    const endDate = new Date(document.getElementById('endDate').value);
    
    return globalData.filter(row => {
        const rowDate = new Date(row.Modified);
        return rowDate >= startDate && rowDate <= endDate;
    });
}

function initializeDashboard() {
    const dates = globalData.map(row => new Date(row.Modified));
    const minDate = new Date(Math.min(...dates));
    const maxDate = new Date(Math.max(...dates));
    
    document.getElementById('startDate').value = minDate.toISOString().split('T')[0];
    document.getElementById('endDate').value = maxDate.toISOString().split('T')[0];
    
    updateDashboard();
}

function resetDateFilter() {
    initializeDashboard();
}
</script>
</body>
</html>
