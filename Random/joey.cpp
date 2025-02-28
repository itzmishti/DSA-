import streamlit as st
import os

# Initialize session state to store chat history
if "chat_history" not in st.session_state:
    st.session_state["chat_history"] = []

# Custom CSS for better UI
st.markdown("""
<style>
    /* Sticky header styling */
    .header-container {
        position: fixed;
        top: 0;
        left: 0;
        right: 0;
        z-index: 999;
        background-color: white;
        padding: 1rem;
        border-bottom: 1px solid #e6e6e6;
    }
    
    /* Main container styling to accommodate fixed header */
    .main-container {
        margin-top: 5rem;
        display: flex;
        flex-direction: column;
        height: calc(100vh - 10rem);
    }
    
    /* Chat container styling */
    .chat-container {
        overflow-y: auto;
        height: 70vh;
        padding: 1rem;
        margin-bottom: 1rem;
        border: 1px solid #e6e6e6;
        border-radius: 0.5rem;
    }
    
    /* Message styling */
    .user-message {
        background-color: #e6f7ff;
        padding: 0.5rem 1rem;
        border-radius: 0.5rem;
        margin-bottom: 0.5rem;
        text-align: right;
    }
    
    .assistant-message {
        background-color: #f0f0f0;
        padding: 0.5rem 1rem;
        border-radius: 0.5rem;
        margin-bottom: 0.5rem;
    }
    
    /* Remove padding from Streamlit containers */
    .block-container {
        padding-top: 1rem;
        padding-bottom: 1rem;
    }
</style>
""", unsafe_allow_html=True)

# Fixed header
st.markdown('<div class="header-container"><h1>Chat with Assistant</h1></div>', unsafe_allow_html=True)

# Main container with chat history and input
st.markdown('<div class="main-container">', unsafe_allow_html=True)

# Chat container
chat_container = st.container()
with chat_container:
    st.markdown('<div class="chat-container">', unsafe_allow_html=True)
    
    # Display chat history
    for i, (user_msg, assistant_msg) in enumerate(st.session_state["chat_history"]):
        st.markdown(f'<div class="user-message">**User:** {user_msg}</div>', unsafe_allow_html=True)
        st.markdown(f'<div class="assistant-message">**Assistant:** {assistant_msg}</div>', unsafe_allow_html=True)
    
    st.markdown('</div>', unsafe_allow_html=True)

# User input section at the bottom
with st.container():
    user_input = st.text_input("Your message:", key="user_input")
    if st.button("Send", key="send_button"):
        if user_input:
            # Process the user input (add your assistant logic here)
            # This is just a placeholder - replace with your actual chatbot logic
            assistant_response = f"Echo: {user_input}"
            
            # Add to chat history
            st.session_state["chat_history"].append((user_input, assistant_response))
            
            # Clear the input
            st.session_state["user_input"] = ""
            
            # Rerun to update the UI
            st.experimental_rerun()

st.markdown('</div>', unsafe_allow_html=True)

# Optional sidebar for document upload and script execution
with st.sidebar:
    st.title("Sidebar Options")
    
    # File uploader
    uploaded_file = st.file_uploader("Upload a document")
    
    # Add any other sidebar options here
