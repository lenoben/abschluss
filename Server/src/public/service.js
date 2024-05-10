function getfunc(){
    const submitButton = document.getElementById("get-submit-btn");
    const inputText = document.getElementById("get-input-text");
    submitButton.addEventListener("click", async () => {
        //fetch from api
        const key = "sk-wertyuoisnuuxgthc5c";
        inputText.value = key; // fill in input value
        //disable button
        submitButton.disabled = true;
        console.log("wertyu");
    })
}

function copygetfunc(){
    const submitButton = document.getElementById("get-copy-btn");
    const inputText = document.getElementById("get-input-text");
    submitButton.addEventListener("click", async () => {
        if(inputText.value === ""){
            return;
        }else{
            inputText.select();
            inputText.setSelectionRange(0, inputText.value.length);
            document.execCommand('copy');
            window.getSelection().removeAllRanges();
            // navigator.clipboard.writeText(inputText.value);
            submitButton.textContent = "copied()."
        }
    })
}

document.getElementById('NmccopyButton').addEventListener('click', async function () {
    // Get the current URL
    const currentURL = window.location.href;
    
    // Concatenate the URL with "/home/api"
    // const response = await fetch('/api/v1/modeluri');
    // if(response.ok){
    //     const data = response.json();
    //     const concatenatedURL = data.modeluri + '/logreg'
    // }
    const concatenatedURL = currentURL + "/api/v1/nmc";
    
    // Get the input element
    const textInput = document.getElementById('textInput');
    
    // Set the value of the input element to the concatenated URL
    textInput.value = concatenatedURL;
    
    // Select the text inside the input element
    textInput.select();
    
    // Copy the selected text to the clipboard
    document.execCommand('copy');
});


document.getElementById('LogregcopyButton').addEventListener('click', async function () {
    // Get the current URL
    const currentURL = window.location.href;
    
    // Concatenate the URL with "/home/api"
    // const response = await fetch('/api/v1/modeluri');
    // if(response.ok){
    //     const data = response.json();
    //     const concatenatedURL = data.modeluri + '/logreg'
    // }
    const concatenatedURL = currentURL + "/api/v1/logreg";
    
    // Get the input element
    const textInput = document.getElementById('textInput');
    
    // Set the value of the input element to the concatenated URL
    textInput.value = concatenatedURL;
    
    // Select the text inside the input element
    textInput.select();
    
    // Copy the selected text to the clipboard
    document.execCommand('copy');
});

document.addEventListener("DOMContentLoaded", function() {
    getfunc();
    copygetfunc();
});