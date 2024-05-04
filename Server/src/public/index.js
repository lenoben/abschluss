function probs(btndiv, model){
            const model_btn_div = document.createElement('div');
            model_btn_div.classList.add("flex","gap-2","mt-2");
            const model_btn = document.createElement('button');
            const model_btn2 = document.createElement('button');
            if(model.result == 1){
                model_btn.classList.add("w-24","h-9","flex","items-center","justify-center","bg-green-950","rounded");
                model_btn.textContent = "positive";
                model_btn_div.appendChild(model_btn);
                model_btn2.classList.add("w-24","h-9","flex","items-center","justify-center","bg-green-950","rounded");
                model_btn2.textContent = model.probability * 100 + "%";
                model_btn_div.appendChild(model_btn2);
            }else{
                model_btn.classList.add("w-24","h-9","flex","items-center","justify-center","bg-red-950","rounded");
                model_btn.textContent = "negative";
                model_btn_div.appendChild(model_btn);
                model_btn2.classList.add("w-24","h-9","flex","items-center","justify-center","bg-red-950","rounded");
                model_btn2.textContent = model.probability * 100 + "%";
                model_btn_div.appendChild(model_btn2);
            }
            btndiv.appendChild(model_btn_div);
}

function nonprob(btndiv, model){
    const modeldoc_btn = document.createElement('button');
    if(model.result == 1){
        modeldoc_btn.classList.add("w-24","h-9","flex","items-center","justify-center","bg-green-950","rounded");
        modeldoc_btn.textContent = "positive";
    }else{
        modeldoc_btn.classList.add("w-24","h-9","flex","items-center","justify-center","bg-red-950","rounded");
        modeldoc_btn.textContent = "negative";
    }
    
    btndiv.appendChild(modeldoc_btn);
}


/**
 * 
 * @param { actual text } text 
 * @param {* object.{type, user, result, probability}} model
 */
function decentCard(text, model){
    const cardList = document.getElementById("card-list");
    //create new card element
    const card = document.createElement('div');
    card.classList.add("shadow-lg", "rounded-lg", "p-2", "w-3/4", "text-white", "bg-transparent");
    // Set text content
    const textElement = document.createElement('p');
    textElement.classList.add('text-lg');
    textElement.textContent = text;
    card.appendChild(textElement);

     // Set user content
     const userElement = document.createElement('p');
     userElement.classList.add('text-lg', 'mb-2', 'text-blue-500');
     userElement.textContent = 'User: ' + model.user;
     card.appendChild(userElement);

    const btndiv = document.createElement('div');     
    const modeldoc = document.createElement('p');

    modeldoc.classList.add('text-lg','font-bold','mt-2');

    // 🚫 Supports only NMC and Logreg, modify to support more
    switch (model.type) {
        case "logreg":
            modeldoc.textContent = "Logistic regression";
            btndiv.appendChild(modeldoc);
            probs(btndiv, model);
            break;
        case "nmc":
            modeldoc.textContent = "NMC";
            btndiv.appendChild(modeldoc);
            nonprob(btndiv, model);
            break;
    
        default:
            modeldoc.textContent = "unknown";
            btndiv.appendChild(modeldoc);
            nonprob(btndiv, model);
            break;
    }
     card.appendChild(btndiv);
     cardList.insertBefore(card, cardList.firstChild);
}

document.addEventListener("DOMContentLoaded", function() {
    const submitButton = document.getElementById("submit-btn");
    const inputText = document.getElementById("r1");

    submitButton.addEventListener("click", async () => {
        const inputValue = inputText.value.trim();
        if (inputValue === '') {
            return;
        }
        inputText.value = ''; // Clear input

        try {
            const responseLog = await fetch('/api/v1/logreg', {
                method: 'POST',
                body: JSON.stringify({ data: inputValue }),
                headers: {
                    'Content-Type': 'application/json'
                }
            })

            const responseLog2 = await fetch('/api/v1/nmc', {
                method: 'POST',
                body: JSON.stringify({ data: inputValue }),
                headers: {
                    'Content-Type': 'application/json'
                }
            })

            if (responseLog.ok) {
                const responseData = await responseLog.json();
                console.log(responseData);
                decentCard(inputValue, responseData);

            } else {
                // 🚫 send the error message to the database??
                console.error('Error sending data:', responseLog.status);
            }

            if (responseLog2.ok) {
                const responseData2 = await responseLog2.json();
                console.log(responseData2);
                decentCard(inputValue, responseData2);

            } else {
                // 🚫 send the error message to the database??
                console.error('Error sending data:', responseLog2.status);
            }
        } catch (error) {
            // 🚫 send the error message to the database??
            console.error('An error occurred:', error);
        }
    });
});