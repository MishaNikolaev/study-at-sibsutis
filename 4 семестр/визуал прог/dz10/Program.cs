
using dz10.Controllers;
using dz10.Repository;
using dz10.Services;
using WebApplication2.Repositories;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddCors(options =>
{
    options.AddPolicy("AllowReactApp",
        policy => policy.WithOrigins("http://localhost:3000") 
            .AllowAnyMethod()
            .AllowAnyHeader());
});


builder.Services.AddSingleton<ICommentRepository, CommentRepository>();
builder.Services.AddScoped<ICommentServices, CommentService>();

var app = builder.Build();

app.UseCors("AllowReactApp");

app.MapCommentsController();

app.Run();