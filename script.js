const pass_field=document.querySelector(".pass-key");
const showBt=document.querySelector(".show");
showBt.addEventListner("click",function(){
  if(pass_field.type==="password"){
    pass_field.type="text";
    showBt.textContent="HIDE";
    showBt.style.color="#3498db";
  }
  else{
    pass_field.type="password;
    showBt.textContent="SHOW";
    showBt.style.color="#222";
  }
});
