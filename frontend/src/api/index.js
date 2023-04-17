import axios from "axios";

if (process.env.NODE_ENV === "development") {
  axios.defaults.baseURL = "http://127.0.0.1:5555";
}

async function requestFiles() {
  try {
    return await axios.get("/file");
  } catch (e) {
    console.error(e);
    return false;
  }
}

async function requestCurses() {
  try {
    return await axios.get("/curses");
  } catch (e) {
    console.error(e);
    return false;
  }
}

async function requestMusic() {
  try {
    return await axios.get("/music");
  } catch (e) {
    console.error(e);
    return false;
  }
}

async function upload(data, onload) {
  try {
    axios.defaults.onUploadProgress = onload;

    return await axios.post("/file", data, {
      headers: {
        "Content-Type": "multipart/form-data",
      },
    });
  } catch (e) {
    return false;
  }
}

async function requestFile(file) {
  try {
    return await axios.get("/file", {
      params: {
        hash: file.hash,
      },
      responseType: "blob",
    });
  } catch (e) {
    return false;
  }
}

async function screenOff() {
  try {
    return await axios.post("/screen", { "mode": "off" }, {
      headers: {
        "Content-Type": "application/json"
      },
    });
  } catch (e) {
    return false;
  }
}

async function saveNote(name, value) {
  try {
    return await axios.post("/notes", {name, value}, {
      headers: {
        "Content-Type": "multipart/form-data"
      },
    });
  } catch (e) {
    return false;
  }
}

const api = {
  requestFiles,
  requestCurses,
  upload,
  requestFile,
  requestMusic,
  screenOff,
  saveNote,
};

export default api;
