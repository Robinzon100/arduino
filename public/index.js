const onBtn = document.querySelector(".on_button")
const offBtn = document.querySelector(".off_button")


const sendLedState = async (state) => {
    const domainName = document.querySelector("[name='domainName']").dataset.domain
    console.log("sending kuku");

    const response = await fetch(`state`, {
        method: 'POST',
        headers: {
            'Accept': 'application/json',
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ state: state })
    });
}


onBtn.addEventListener('click', () => {
    sendLedState(onBtn.dataset.state)
}
)
offBtn.addEventListener('click', () => {
    sendLedState(offBtn.dataset.state)
}
)
