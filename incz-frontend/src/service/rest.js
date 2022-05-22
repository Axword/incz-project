import Http from "./http";

class Rest extends Http {
  constructor() {
    super();
  }
  get(url, params) {
    return super.fetch('get', url, { params });
  }

  post(url, data) {
    return super.fetch('post', url, data);
  }

  patch(url, data) {
    return super.fetch('patch', url, data);
  }

  put(url, data) {
    return super.fetch('put', url, data);
  }

  delete(url, params) {
    return super.fetch('delete', url, { params });
  }
}


export default Rest;