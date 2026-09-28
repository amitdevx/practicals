// Product Bill using Arrow Function and Template Literals
const generateBill = (productName, price, quantity) => {
    const subtotal = price * quantity;
    const gst = subtotal * 0.18; // 18% GST
    const grandTotal = subtotal + gst;
    return `
=====================================
          RETAIL STORE BILL
=====================================
Product Name : ${productName}
Unit Price   : ₹${price.toFixed(2)}
Quantity     : ${quantity}
-------------------------------------
Subtotal     : ₹${subtotal.toFixed(2)}
GST (18%)    : ₹${gst.toFixed(2)}
-------------------------------------
Grand Total  : ₹${grandTotal.toFixed(2)}
=====================================
`;
};

console.log(generateBill("Wireless Headphones", 2499.00, 2));
