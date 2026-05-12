/* /earc/css/bootframe.css */
/* BootFrame-only styles. Use ONLY on /earc/bootframe/ pages. */

:root {
  --bf-primary: #00ff41;
  --bf-secondary: #ff006e;
  --bf-accent: #00d9ff;
  --bf-dark: #0a0e27;
  --bf-darker: #050812;
  --bf-border: #1a1f3a;
  --bf-text: #e0e6ff;
  --bf-text-dim: #8892b0;
  --bf-glow: 0 0 15px rgba(0, 255, 65, 0.3);
  --bf-user-bg: #1a3a5c;
  --bf-bot-bg: #2a1f3a;
}

* { box-sizing: border-box; }

body.bootframe-isolated {
  margin: 0;
  padding: 0;
  background: linear-gradient(135deg, var(--bf-darker) 0%, #0f1535 100%);
  color: var(--bf-text);
  font-family: 'Courier New', monospace;
  line-height: 1.5;
}

.k501-bootframe {
  height: 100vh;
  display: flex;
  flex-direction: column;
  background: linear-gradient(135deg, var(--bf-darker) 0%, #0f1535 100%);
  color: var(--bf-text);
  padding: 0;
  border-radius: 0;
  overflow: hidden;
  box-shadow: inset 0 0 50px rgba(0, 0, 0, 0.5);
}

.bootframe-header {
  background: linear-gradient(90deg, rgba(10, 14, 39, 0.95) 0%, rgba(15, 21, 53, 0.95) 100%);
  border-bottom: 2px solid var(--bf-primary);
  padding: 16px 20px;
  display: flex;
  justify-content: space-between;
  align-items: center;
  box-shadow: 0 0 20px rgba(0, 255, 65, 0.1);
}

.bootframe-header h1 {
  margin: 0;
  font-size: 18px;
  color: var(--bf-primary);
  text-shadow: var(--bf-glow);
  letter-spacing: 2px;
  text-transform: uppercase;
}

.status-badge {
  background: rgba(0, 255, 65, 0.2);
  border: 1px solid var(--bf-primary);
  color: var(--bf-primary);
  padding: 4px 10px;
  border-radius: 4px;
  font-size: 11px;
  font-weight: 600;
  text-transform: uppercase;
  letter-spacing: 1px;
}

.chat-container {
  flex: 1;
  padding: 20px;
  overflow-y: auto;
  overflow-x: hidden;
  background: linear-gradient(180deg, rgba(5, 8, 18, 0.8) 0%, rgba(10, 14, 39, 0.6) 100%);
  display: flex;
  flex-direction: column;
  gap: 12px;
}

.chat-container::-webkit-scrollbar { width: 8px; }
.chat-container::-webkit-scrollbar-track { background: rgba(0, 0, 0, 0.3); }
.chat-container::-webkit-scrollbar-thumb { background: var(--bf-primary); border-radius: 4px; }
.chat-container::-webkit-scrollbar-thumb:hover { background: var(--bf-accent); box-shadow: 0 0 10px var(--bf-accent); }

.k501-bootframe .msg {
  margin: 0;
  padding: 12px 14px;
  border-radius: 6px;
  max-width: 85%;
  word-wrap: break-word;
  border: 1px solid transparent;
  transition: all 0.3s ease;
}

.k501-bootframe .msg.user {
  background: linear-gradient(135deg, var(--bf-user-bg) 0%, rgba(0, 217, 255, 0.1) 100%);
  color: var(--bf-accent);
  margin-left: auto;
  text-align: right;
  border-color: var(--bf-accent);
  box-shadow: 0 0 15px rgba(0, 217, 255, 0.15);
}

.k501-bootframe .msg.bot {
  background: linear-gradient(135deg, var(--bf-bot-bg) 0%, rgba(0, 255, 65, 0.05) 100%);
  color: var(--bf-text);
  margin-right: auto;
  text-align: left;
  border-color: var(--bf-primary);
  box-shadow: 0 0 15px rgba(0, 255, 65, 0.1);
}

.k501-bootframe .msg.system-note {
  font-style: italic;
  opacity: 0.8;
  font-size: 12px;
  color: var(--bf-text-dim);
  background: rgba(0, 217, 255, 0.08);
  border-color: var(--bf-border);
  margin: 8px auto;
}

.k501-bootframe .meta {
  font-size: 10px;
  color: var(--bf-text-dim);
  margin-top: 6px;
  opacity: 0.7;
}

/* Controls */
#k501-controls {
  display: flex;
  flex-direction: column;
  gap: 12px;
  padding: 16px;
  border-top: 1px solid var(--bf-border);
  background: linear-gradient(90deg, rgba(10, 14, 39, 0.95) 0%, rgba(15, 21, 53, 0.95) 100%);
  box-shadow: 0 -8px 20px rgba(0, 0, 0, 0.3);
}

.input-group { display: flex; gap: 8px; }

.chat-input {
  flex: 1;
  padding: 10px 14px;
  font-size: 14px;
  border: 1px solid var(--bf-border);
  border-radius: 6px;
  background: rgba(0, 0, 0, 0.3);
  color: var(--bf-text);
  font-family: 'Courier New', monospace;
}

.chat-input:focus {
  outline: none;
  border-color: var(--bf-primary);
  box-shadow: 0 0 15px rgba(0, 255, 65, 0.2);
  background: rgba(0, 0, 0, 0.5);
}

.chat-input::placeholder { color: var(--bf-text-dim); }

.send-button {
  padding: 10px 16px;
  font-size: 14px;
  border-radius: 6px;
  border: 1px solid var(--bf-primary);
  background: linear-gradient(135deg, rgba(0, 255, 65, 0.2) 0%, rgba(0, 217, 255, 0.1) 100%);
  color: var(--bf-primary);
  cursor: pointer;
  font-weight: 600;
  text-transform: uppercase;
  letter-spacing: 1px;
  font-family: 'Courier New', monospace;
}

.send-button:disabled { opacity: 0.4; cursor: not-allowed; }

.control-buttons { display: flex; gap: 8px; }

.control-btn {
  flex: 1;
  padding: 8px 12px;
  font-size: 12px;
  border-radius: 6px;
  border: 1px solid var(--bf-border);
  background: rgba(0, 217, 255, 0.1);
  color: var(--bf-accent);
  cursor: pointer;
  text-transform: uppercase;
  letter-spacing: 0.5px;
  font-family: 'Courier New', monospace;
  font-weight: 600;
}

#k501-snapshot-info {
  font-size: 11px;
  color: var(--bf-text-dim);
  padding: 10px 14px;
  border-top: 1px solid var(--bf-border);
  background: rgba(0, 217, 255, 0.05);
  line-height: 1.4;
}

.snapshot-info { border-left: 2px solid var(--bf-primary); padding-left: 12px !important; }

@media (max-width: 768px) {
  .k501-bootframe .msg { max-width: 95%; }
  .bootframe-header h1 { font-size: 16px; }
  #k501-controls { gap: 10px; padding: 12px; }
  .control-buttons { flex-direction: column; }
  .control-btn { padding: 10px; font-size: 11px; }
}

@media (max-width: 480px) {
  .chat-container { padding: 12px; }
  .k501-bootframe .msg { max-width: 100%; padding: 10px 12px; }
  .input-group { flex-direction: column; }
  .send-button { padding: 12px; }
}