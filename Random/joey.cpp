<style>
/* Page container adjustments */
.main .block-container {
    display: flex;
    flex-direction: column;
    height: 98vh;
    padding: 0;
}

/* Title styling */
h1 {
    padding: 1rem 0;
    background-color: #262730;
    position: sticky;
    top: 0;
    z-index: 999;
    margin: 0;
}

/* Create scrollable area for chat with fixed height */
[data-testid="stVerticalBlock"] > div:nth-of-type(1) {
    height: 70vh;
    overflow-y: auto;
    display: flex;
    flex-direction: column;
}

/* Input area fixed at bottom */
[data-testid="stVerticalBlock"] > div:nth-of-type(2) {
    position: sticky;
    bottom: 0;
    background-color: #262730;
    padding: 1rem 0;
    margin-top: auto;
    border-top: 1px solid #4e4e4e;
}

/* Make sure text input and button are easily visible */
.stTextInput, .stButton {
    padding: 0.5rem;
}
</style>
