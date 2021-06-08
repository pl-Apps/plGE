const discordrpc = require("discord-rpc")
const rpc = new discordrpc.Client({ transport: 'ipc'});

rpc.on("ready", async() => {
    rpc.setActivity({
        details: "HEHEHEHEHEHEHHE",
        state: "asdjasdjkasd",
                
    })
})

rpc.login({ clientId: "851869772047319123"})