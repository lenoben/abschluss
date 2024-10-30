document.getElementById('NmccopyButton').addEventListener('click', async function () {
    const currentURL = window.location.href;
    const concatenatedURL = currentURL + "/api/v1/nmc";
    const textInput = document.getElementById('textInputNMC');
    textInput.value = concatenatedURL;
    textInput.select();
    document.execCommand('copy');
});


document.getElementById('LogregcopyButton').addEventListener('click', async function () {
    const currentURL = window.location.href;
    const concatenatedURL = currentURL + "/api/v1/logreg";
    const textInput = document.getElementById('textInputLOG');
    textInput.value = concatenatedURL;
    textInput.select();
    document.execCommand('copy');
});