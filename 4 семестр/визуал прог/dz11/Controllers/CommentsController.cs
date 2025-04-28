using dz10.Model;
using dz10.Services;
using Microsoft.AspNetCore.Mvc;

namespace dz10.Controllers;

public static class CommentsController
{
    public static void MapCommentsController(this WebApplication app)
    {
        app.MapGet("/", () => "Ufk");
        
        app.MapGet("/comments", async (ICommentServices commentService) =>
        {
            var comments = commentService.GetAllComments();
            return Results.Ok(comments);
        });

        app.MapGet("/comments/{id}", async (int id, ICommentServices commentService) =>
        {
            var comment = commentService.GetCommentById(id);
            return comment is not null ? Results.Ok(comment) : Results.NotFound();
        });

        app.MapPost("/comments", async ([FromBody] Comment comment, ICommentServices commentService) =>
        {
            var createdComment = commentService.AddComment(comment);
            return Results.Created($"/comments/{createdComment.Id}", createdComment);
        });

        app.MapPatch("/comments/{id}", async (int id, [FromBody] Comment comment, ICommentServices commentService) =>
        {
            var updatedComment = commentService.UpdateComment(id, comment);
            return updatedComment is not null ? Results.Ok(updatedComment) : Results.NotFound();
        });

        app.MapDelete("/comments/{id}", async (int id, ICommentServices commentService) =>
        {
            var success = commentService.DeleteComment(id);
            return success ? Results.NoContent() : Results.NotFound();
        });
    }
}