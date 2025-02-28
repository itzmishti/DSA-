<style>
/* Make the title sticky at the top */
.block-container > div:first-child {
    position: sticky;
    top: 0;
    background-color: #262730;
    z-index: 999;
    padding: 1rem 0;
}

/* Create a container for chat messages with fixed height */
.stChatMessageContent {
    max-height: 70vh;
    overflow-y: auto;
    padding-bottom: 20px;
}

/* Ensure the input area stays at the bottom */
.stTextInput, .stButton {
    position: sticky;
    bottom: 20px;
    padding-top: 10px;
    background-color: #262730;
}
</style>
