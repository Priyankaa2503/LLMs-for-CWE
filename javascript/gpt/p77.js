function createPerson() {
  // object allocation in JS
  const person = {};
  person.status = 0;
  return person;
}

const newPerson = createPerson();
console.log("Person status:", newPerson.status);
