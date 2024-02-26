"use strict";

async function load_wasm(wasm_binary) {
    return new Promise((resolve) => {
        let worker = new Worker('dist/worker.js');
        worker.onmessage = ({ data }) => {
            const [id, message, value] = data;
            const element = document.getElementById(id);
            if (element) {
                const textArea = element;
                switch (message) {
                    case 'set':
                        textArea.value = value;
                        break;
                    case 'append':
                        textArea.value += value;
                        break;
                    case 'final':
                        textArea.value += value;
                        worker.terminate();
                        worker = undefined;
                        resolve('Done');
                }
            }
        };
        worker.postMessage(wasm_binary);
    });
}
