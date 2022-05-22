function objectHandler(setter) {
  return {
    get(obj, prop) {
      if (!(prop in obj)) {
        setter({ prop, value: undefined });
      }
      return obj[prop];
    },
    set(obj, prop, value) {
      setter({ prop, value });
      return true;
    },
  };
}

function paginationAdapter(pagination, rest) {
  let paginationObject = {
    offset: (pagination.page - 1) * pagination.itemsPerPage,
    limit: pagination.itemsPerPage,
    ...rest,
  };
  paginationObject = { ...paginationObject, ...pagination.filterOptions };
  if (pagination.sortBy && pagination.sortBy.length) {
    const orderingSign = pagination.sortDesc[0] ? "-" : "";
    paginationObject.ordering = `${orderingSign}${pagination.sortBy[0]}`;
  }
  return paginationObject;
}

export { objectHandler, paginationAdapter };
