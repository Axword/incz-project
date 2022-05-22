import Rest from './rest';



class RestObject {
  static async list(params) {
    const rest = new Rest();
    try {
      const response = await rest.get(this.URL, params);
      const objects = response.data.results.map(obj => new this(obj));
      objects.count = response.data.count;
      return objects;
    } catch (err) {
      throw err.response.data;
    }
  }
  static async get(id, params) {
    const rest = new Rest();
    try {
      const response = await rest.get(`${this.URL}${id}/`, params);
      return new this(response.data);
    } catch (err) {
      throw err.response.data;
    }
  }

  async save() {
    const rest = new Rest();
    try {
      const response = this.id
        ? await rest.patch(`${this.constructor.URL}${this.id}/`, this)
        : await rest.post(this.constructor.URL, this);
      Object.assign(this, response.data);
      return this;
    } catch (err) {
      throw err.response.data;
    }
  }

  async remove() {
    const rest = new Rest();
    try {
      await rest.delete(`${this.constructor.URL}${this.id}/`);
    } catch (err) {
      throw err.response.data;
    }
  }
}
RestObject.URL = null;

export default RestObject;
