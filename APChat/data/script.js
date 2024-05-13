let settings;
async function getSettings() {
    let settingsResponse = await fetch('/chat/settings', {method:'POST'});
    settings = JSON.parse(await settingsResponse.text())[0];
    document.getElementById('log').rows = settings.max_logs_count;
    document.getElementById('log').cols = settings.max_name_size + 4 + settings.max_message_size;
}
getSettings();

function onButtonClick() {
    let nick = document.getElementById('nick').value;
    let message = document.getElementById('message').value;
    if (nick == '' || message == '' || nick.length > settings.max_name_size || message.length > settings.max_message_size) {
        alert('Please fill all fields correctly!');
        return;
    }
    fetch(`/chat/send?nick=${nick}&message=${message}`, {method:'POST'});
    document.getElementById('message').value = '';
}
document.getElementById('send').addEventListener('click',onButtonClick,false);

async function updateChatLog() {
    let updateResponse = await fetch('/chat/get',{method:'POST'});
    let messages = JSON.parse(await updateResponse.text());
    document.getElementById('log').innerHTML = '';
    for (let i = 0, message; i < messages.length; ++i) {
        message = messages[i];
        document.getElementById('log').innerHTML += `[${message.nick}]: ${message.message}\n`;
    }
}
setInterval(updateChatLog,2500);