using dz10.Model;

namespace dz10.Services;

public interface ICommentServices
{
    IEnumerable<Comment> GetAllComments();
    Comment? GetCommentById(int id);
    Comment AddComment(Comment comment);
    Comment? UpdateComment(int id, Comment comment);
    bool DeleteComment(int id);
}