


void update_amount(string payload) {
  AddAmountRequest* amount_request = new AddAmountRequest();
  amount_request->ParseFromString(payload);

  string account_name = amount_request.name();
  if (accounts.counts(account_name)) {
    accounts[account_name] += amount_request.value();
  } else {
    accounts[account_name] = amount_request.value();
  }

  return;
}
