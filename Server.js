const WebSocket = require('ws');

// WebSocket-Server auf Port 3000 starten
const wss = new WebSocket.Server({ port: 3000 });

wss.on('listening', () => {
  console.log('WebSocket-Server läuft auf ws://localhost:3000');
});

wss.on('connection', (ws) => {
  console.log('WebSocket verbunden!');

  ws.on('message', (message) => {
    console.log(`Nachricht erhalten: ${message}`);

    // Broadcast an ALLE verbundenen Clients (außer dem Sender optional)
    wss.clients.forEach((client) => {
      if (client !== ws && client.readyState === WebSocket.OPEN) {
        client.send(message);
      }
    });
  });

  ws.on('close', () => {
    console.log('Client getrennt');
  });
});

