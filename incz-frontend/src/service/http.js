import axios from "axios";
import Qs from "qs";

axios.defaults.paramsSerializer = (params) =>
  Qs.stringify(params, {
    arrayFormat: "repeat",
  });

class Http {
  constructor() {
    this.http = axios.create(this.getConfig());
  }

  fetch(method, url, params) {
    return this.http[method](url, params);
  }

  getConfig() {
    return {
      headers: {
        "Content-Type": "application/json",
      },
      baseURL: "http://192.168.61.17:8000/",
    };
  }
}

export default Http;
